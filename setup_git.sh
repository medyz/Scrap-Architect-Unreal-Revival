#!/usr/bin/env bash
set -euo pipefail

echo "Initializing Git repository..."
git init

echo "Adding all files..."
git add -A

if git rev-parse --verify HEAD >/dev/null 2>&1; then
  echo "Committing changes..."
  git commit -m "chore: project setup updates" || echo "Nothing to commit."
else
  echo "Creating initial commit..."
  git commit -m "Initial commit: Scrap Architect Unreal Revival project setup"
fi

REMOTE_URL="${1:-}"
if [[ -n "$REMOTE_URL" ]]; then
  echo "Configuring remote origin: $REMOTE_URL"
  if git remote | grep -q "^origin$"; then
    git remote set-url origin "$REMOTE_URL"
  else
    git remote add origin "$REMOTE_URL"
  fi
  CURRENT_BRANCH="$(git symbolic-ref --short HEAD 2>/dev/null || echo main)"
  echo "Pushing to origin/$CURRENT_BRANCH..."
  git push -u origin "$CURRENT_BRANCH"
else
  echo "No remote URL provided. Skipping push."
  echo "Usage: ./setup_git.sh <remote-url>"
fi

echo "Done."

