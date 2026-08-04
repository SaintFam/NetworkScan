param(
  [string]$Message
)

if (-not $Message) { $Message = Read-Host "Commit message" }

git add -A
git commit -m "$Message"

git push
if ($LASTEXITCODE -ne 0) {
  Write-Host "Push failed; attempting to set upstream to origin/main and push."
  git push -u origin main
}
