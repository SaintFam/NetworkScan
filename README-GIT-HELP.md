This repository helper provides two PowerShell scripts to simplify working with Git on Windows.

Files created:
- reset_remote_history.ps1 — Replace the remote repository history with your local repository (destructive). Use with care.
- git_quick.ps1 — Simple helper to `add`, `commit`, and `push` in one step.

Quick usage:

1) To make the remote repository a fresh copy of your local repo (THIS DELETES REMOTE HISTORY):

   In PowerShell, run:

   .\reset_remote_history.ps1

   You will be asked to confirm by typing `Y`.

2) To commit and push changes quickly:

   - Run interactively and enter a message when prompted:

     .\git_quick.ps1

   - Or pass a message directly:

     .\git_quick.ps1 -Message "Fix bug"

Notes:
- The force push requires authentication to GitHub; PowerShell/Windows will prompt for credentials or use your credential helper.
- Keep a backup if you need the previous remote history.
