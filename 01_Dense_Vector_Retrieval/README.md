<p align = "center" draggable="false" ><img src="https://github.com/AI-Maker-Space/LLM-Dev-101/assets/37101144/d1343317-fa2f-41e1-8af1-1dbb18399719"
     width="200px"
     height="auto"/>
</p>

<h1 align="center" id="heading">Session 1: Dense Vector Retrieval</h1>

### [Quicklinks]()

| 📰 Module Sheet                                                                 | ⏺️ Recording | 🖼️ Slides | 👨‍💻 Repo       | 📝 Homework | 📁 Feedback |
| :------------------------------------------------------------------------------- | :----------- | :-------- | :------------ | :---------- | :---------- |
| [Dense Vector Retrieval](../00_Docs/Modules/01_Dense_Vector_Retrieval/README.md) |[Recording!](https://us02web.zoom.us/rec/share/sHWvo0Nd1aI0SEhKecOLEX9kFGVJJAdYfsKiuTmm8t85W48Z2lnjpnzTy8jAd8R5.PwuqibGwAZhvDd8c) <br> passcode: `C62n^@Q!`| [Session 1 Slides](https://canva.link/htfqf8i39yejyhn) | You are here! | [Session 1 Assignment](https://forms.gle/Z9qskfVaAvPjn6gz8) | [Feedback 6/2](https://forms.gle/21a2uoL9DVZPwgJP6) |


## 🏗️ How AIM Does Assignments

> 📅 **Assignments will always be released to students as live class begins.** We will never release assignments early.

Each assignment will have a few of the following categories of exercises:

- ❓ **Questions** - these will be questions that you will be expected to gather the answer to. These can appear as general questions, or questions meant to spark a discussion in your breakout rooms.

- 🏗️ **Activities** - these will be work or coding activities meant to reinforce specific concepts or theory components.

- 🚧 **Advanced Builds (optional)** - Take on a challenge. These builds require you to create something with minimal guidance outside of the documentation.

## Main Assignment

In this assignment, you will build a vector RAG application using LangChain v1, OpenAI embeddings, and Qdrant.

The main notebook is:

```text
01_Cat_Health_Vector_RAG_LangChain_Qdrant.ipynb
```

The notebook uses the bundled cat health guideline PDF in `data/cat_health_guidelines.pdf`.

### Setup

From this folder, install the environment with uv:

```bash
uv sync
```

Then open the notebook in Cursor or VS Code and select the Python/Jupyter environment created by uv.

You will also need an OpenAI API key available when running the notebook.

---

## 🏗️ Activity #1: Embedding Similarity

Run the embedding similarity primer in the notebook.

You will compare embeddings for terms like:

- `king`
- `queen`
- `banana`
- `cat`
- `veterinarian`
- `cat health guidelines`

#### ❓Question #1

Why is cosine similarity useful for dense vector retrieval?

Cosine Similarity score helps me to understand the degree to which two vectors (sentence vectors , document vectors, word vectors) are similar to each other contextually (it may not convey similarity in the exact meaning). 
Cosine similairty becomes a metric to compare the user query and the chunks stored in the Vector DB and hence retrieve the contextually similar chunks from the vector DB which when passed to the LLM, generates a response to the USer Query! 🛺🪶🧑‍🚀🚀✈️



##### ✅ Answer:

---

## 🏗️ Activity #2: Build the Vector RAG Pipeline

Run the notebook sections that:

1. Load the PDF into LangChain `Document` objects
2. Split the document into chunks
3. Embed the chunks
4. Store the chunk embeddings in in-memory Qdrant
5. Retrieve relevant chunks with similarity scores
6. Generate an answer grounded in retrieved context

#### ❓Question #2

Why is metadata important for a RAG application?
##### ✅ Answer:
✈️🧑‍🚀🚀👨‍🚀
1. It gives us information about the length of the document which can help us to compare if the loader actually loaded all the pages of the document. IT can be a useful tool to help prevent data loss.
2. You can filter the vector database on the basis of different fields of the metadata.
3. Displaying information about the source of the data in your output can help with transparency that builds trust.
4. It helps us to debug when there is hallucination. There are times when the output drifts due to different dataset revisions and the responses can be hallucinated. With metadata it helps us to compare the hallucinated version with another version that didn't hallucinate and this gives us a big clue for troubleshooting hallucination.
5. Also, we will know about the source of the data through metadata and hence we can go to the exact document and page/paragrpah ourselves for more information
✈️✈️🎆🎆

##### ✅ Answer:

#### ❓Question #3

What tradeoff do we make when choosing chunk size and chunk overlap?

##### ✅ Answer:
1.Smaller the overlap, or no overlap, would mean that all the context at the chunk break hasn't been captured and the response probably would not make sense or can hallucinate.  ⛹️⛹️

2.Bigger the overlap would mean that we are adding redundancy into the chunks and exhaust the token limit faster making the application expensive.
🍿🧂
 
3.Smaller the chunks for a given document would mean more latency for storage and retrieval from the vector DB as we would occupy more space in the vector DB. 🤦‍♀️🤦‍♂️🤷‍♀️

4.Bigger the chunk size could mean that we are feeding more info to the LLM than it needs and there is a chance it doesn't pick all the needed info from the chunks results in insufficient data retrieval.  🍿🧂

#### ❓Question #4

What does a similarity score help you understand, and what does it not prove by itself?

##### ✅ Answer:
A) Similarity score helps me to understand the degree to which two vectors (sentence vectors , document vectors, word vectors) are similar to each other contextually (it may not convey similarity in the exact meaning).
For example, king and queen are contextually similar in their usage with a high similarity score than king vs banana, but (king, queen) are not the same in their meaning. ⛹️‍♀️⛹️‍♂️⛹️

king <> queen                  score=0.591

king <> banana                 score=0.310

B) However, the score by itself does not prove anything unless it is compared to others scores in the Vector DB. 😒 So we rank the similairty scores and that gives us an idea of the most contextually similarity scores 🎇🎆 
---

## 🏗️ Activity #3: Vibe Check Retrieval Quality

Run the notebook's vibe check queries and inspect both:

- The retrieved context
- The generated answer

#### ❓Question #5

For the vibe check queries, did the retrieved context seem relevant before generation? Why or why not?

##### ✅ Answer:

---Story goes:

Round 1 of experimentations!!!!! ✈️👨‍🚀🚀🧑‍🚀🪶
So I played around with chunk size (1000) ,overlap (200). For the question, "diseases commonly seen in young adult cats",  the retrieved context didn't contain information for the query and so was irrelevant. Even after increasing the no. of chunks to 4, the context was not relevant.

Round 2 of experimentation!!!!!! 🍿🍿🍿🍿🍿
Increased the chunk size to 1500, even reduced chunk size back to 2, modified query slightly. Now the relevant context was relevant. The generation was pretty crisp and accurate.

Conclusions 🚕🚕🚕🛺🛺🚒
1. You should experiment with chunk size/ no. of retrieved chunks (k) to ensure you are seeing accurate results and not just assume that the retrieved context will always be relevant.
2. Also, when the LLM was prompted about context in Table 3 where the data was inside a table, the relevant context couldn't pull the data from the table and so the generation said it doesn't have required information. Maybe using another loader would be useful for reading tabular data.

So I saw that the retrieved context either did contain relevant context or didn't based on experimentation above and on the basis of the limitations of the loader. 🤷‍♀️🤷‍♀️🤷‍♀️🤷‍♀️


## 🏗️ Activity #4: Tune Retrieval

Improve retrieval quality by changing one or more of:

- Chunk size
- Chunk overlap
- Retrieval `k`
- Query wording

Document what changed and whether retrieval improved.

##### Settings Changed:

-

##### Results:
 
1.  Initially chunk size was 1000, overlap 100 , k = 3 . The response said it doesn't have enough information.
2. Changed the chunk size to 1500,  k = 2, changed the query to make it concise and very sepcific and now the information retrieved was accurate.


---

## Optional Deep Dive: RAG From Scratch

If you want to look underneath the library abstractions, run the optional reference notebook:

```text
02_Cat_Health_Vector_RAG_From_Scratch.ipynb
```

It builds the same retrieval pipeline again with only:

- `pypdf` for extracting text from the PDF
- Python standard-library HTTP requests for calling OpenAI
- Handcrafted document, chunking, embedding, similarity-search, vector-store, and generation primitives

This notebook is a reference walkthrough, not an additional assignment. Its purpose is to make the responsibilities hidden by LangChain, Qdrant, and provider SDKs visible.

---

## Submitting Your Homework

### Main Assignment

Follow these steps to prepare and submit your homework:

1. Pull the latest updates from upstream into the main branch of your AIE9 repo:

```bash
git checkout main
git pull upstream main
git push origin main
```

2. Start Cursor from the `01_Dense_Vector_Retrieval` folder.
3. Complete the notebook.
4. Answer the questions in this `README.md`.
5. Add, commit, and push your modified work to your origin repository.

When submitting your homework, provide the GitHub URL to your AIE9 repo.
