from __future__ import annotations

import asyncio
import json
from dataclasses import dataclass, replace
from typing import Iterable, Sequence
import os
import re
import shutil
import subprocess
import textwrap
from datetime import date
from getpass import getpass
from pathlib import Path
from typing import Literal, TypedDict

from IPython.display import Markdown, display
from pydantic import BaseModel, Field

from langchain.agents import create_agent
from langchain.agents.middleware import (
    ModelCallLimitMiddleware,
    ToolCallLimitMiddleware,
)
from langchain.messages import ToolMessage
from langchain.tools import tool
from langchain_core.runnables import RunnableConfig
from langchain_openai import ChatOpenAI, OpenAIEmbeddings
from langchain_core.documents import Document
from langchain_qdrant import QdrantVectorStore
from docling.document_converter import DocumentConverter
from docling_core.transforms.chunker import HierarchicalChunker
from rank_bm25 import BM25Okapi

from langgraph.checkpoint.memory import InMemorySaver
from langgraph.graph import END, START, StateGraph
