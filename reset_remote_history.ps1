param(
  [string]$RemoteUrl = "https://github.com/SaintFam/NetworkScan.git"
)

Write-Host "WARNING: This will REPLACE the remote repository history with your local repository."
$confirm = Read-Host "Type Y to continue"
if ($confirm -ne 'Y') { Write-Host "Cancelled."; exit 1 }

if (-not (Test-Path .git)) {
  git init
}

git add -A
try {
  git commit -m "Initial commit - reset remote history"
} catch {
  Write-Host "No changes to commit or commit failed; continuing"
}

git branch -M main
git remote remove origin 2>$null
git remote add origin $RemoteUrl

Write-Host "Force-pushing to origin/main (destructive)..."
git push --force origin main
Write-Host "Done. Remote history has been replaced."
