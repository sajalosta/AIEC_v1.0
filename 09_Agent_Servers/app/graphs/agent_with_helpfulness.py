"""Agent graph with a post-response helpfulness evaluation loop."""

from __future__ import annotations

from langchain_core.messages import AIMessage, SystemMessage
from langchain_core.output_parsers import StrOutputParser
from langchain_core.prompts import ChatPromptTemplate
from langgraph.graph import END, START, StateGraph
from langgraph.prebuilt import ToolNode

from app.models import fix_tool_calls, get_chat_model
from app.state import MessagesState
from app.tools import get_tool_belt

SYSTEM_PROMPT = (
    "You are a helpful assistant specialized in feline (cat) health. "
    "Use the retrieve_information tool for cat-health questions, web search for "
    "current information, and Arxiv for research papers. Cite tool results when "
    "they inform your answer."
)

MAX_MESSAGES = 10


def _build_model_with_tools():
    model = get_chat_model()
    return model.bind_tools(get_tool_belt())


def call_model(state: MessagesState) -> dict:
    """Invoke the model with tools and append its response."""
    model = _build_model_with_tools()
    messages = list(state["messages"])
    if not messages or not isinstance(messages[0], SystemMessage):
        messages = [SystemMessage(content=SYSTEM_PROMPT), *messages]
    response = fix_tool_calls(model.invoke(messages))
    return {"messages": [response]}


def route_to_action_or_helpfulness(state: MessagesState):
    """Run tools if requested; otherwise evaluate helpfulness."""
    last_message = state["messages"][-1]
    if getattr(last_message, "tool_calls", None):
        return "action"
    return "helpfulness"


_helpfulness_prompt = ChatPromptTemplate.from_template(
    "Given an initial query and a final response, determine if the final response "
    "is extremely helpful or not. Respond with only Y or N.\n\n"
    "Initial Query:\n{initial_query}\n\n"
    "Final Response:\n{final_response}"
)


def helpfulness_node(state: MessagesState) -> dict:
    """Judge whether the latest answer is helpful relative to the user query."""
    if len(state["messages"]) > MAX_MESSAGES:
        return {"messages": [AIMessage(content="HELPFULNESS:END")]}

    initial_query = next(
        (m for m in state["messages"] if getattr(m, "type", None) == "human"),
        state["messages"][0],
    )
    final_response = state["messages"][-1]

    chain = _helpfulness_prompt | get_chat_model() | StrOutputParser()
    result = chain.invoke(
        {
            "initial_query": initial_query.content,
            "final_response": final_response.content,
        }
    )

    decision = "Y" if result.strip().upper().startswith("Y") else "N"
    return {"messages": [AIMessage(content=f"HELPFULNESS:{decision}")]}


def helpfulness_decision(state: MessagesState):
    """End on helpful, retry on not helpful, stop after loop limit."""
    last = state["messages"][-1]
    text = getattr(last, "content", "")
    if text == "HELPFULNESS:END":
        return END
    if "HELPFULNESS:Y" in text:
        return "end"
    return "continue"


def build_graph():
    graph = StateGraph(MessagesState)
    tool_node = ToolNode(get_tool_belt())
    graph.add_node("agent", call_model)
    graph.add_node("action", tool_node)
    graph.add_node("helpfulness", helpfulness_node)
    graph.add_edge(START, "agent")
    graph.add_conditional_edges(
        "agent",
        route_to_action_or_helpfulness,
        {"action": "action", "helpfulness": "helpfulness"},
    )
    graph.add_conditional_edges(
        "helpfulness",
        helpfulness_decision,
        {"continue": "agent", "end": END, END: END},
    )
    graph.add_edge("action", "agent")
    return graph


graph = build_graph().compile()
