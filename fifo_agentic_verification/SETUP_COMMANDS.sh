# Only 3 commands. Copy each into the WSL terminal, in order.
# Command 1 asks for your key: paste it (right-click), press Enter.
# It stays invisible and is never written anywhere.

read -s -p "OpenAI key: " OPENAI_API_KEY && export OPENAI_API_KEY && echo " ...set"

source ~/.venvs/fifo/bin/activate

jupyter nbconvert --to notebook --execute --allow-errors fifo_agentic_verification.ipynb --output run_out.ipynb 2>&1 | tee out.txt

# It runs the whole notebook (takes minutes). When it stops, tell Claude: check
