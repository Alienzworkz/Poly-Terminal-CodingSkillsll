# GitHub Setup Guide

This guide will help you set up your GitHub repository for the CCC project submission.

## Step 1: Create GitHub Account (if needed)

1. Go to https://github.com
2. Click "Sign up"
3. Follow the registration process

## Step 2: Create New Repository

1. Click the "+" icon in the top right
2. Select "New repository"
3. Fill in the details:
   - **Repository name**: `decentralized-trading-terminal`
   - **Description**: `Bloomberg-style trading terminal with Greedy & DP algorithms for CCC project`
   - **Visibility**: Public (required for CCC submission)
   - **Initialize**: Do NOT check any boxes (we already have files)
4. Click "Create repository"

## Step 3: Initialize Git in Your Project

Open terminal/command prompt in your project folder:

```bash
# Initialize git repository
git init

# Add all files
git add .

# Create first commit
git commit -m "Initial commit: Decentralized Trading Terminal with Greedy and DP algorithms"

# Rename branch to main (if needed)
git branch -M main
```

## Step 4: Connect to GitHub

Replace `YOUR_USERNAME` with your GitHub username:

```bash
# Add remote repository
git remote add origin https://github.com/YOUR_USERNAME/decentralized-trading-terminal.git

# Push to GitHub
git push -u origin main
```

## Step 5: Verify Upload

1. Go to your repository on GitHub
2. Verify all files are present:
   - ✓ include/ folder with 4 header files
   - ✓ src/ folder with 5 source files
   - ✓ Documentation files (README.md, etc.)
   - ✓ Build scripts (Makefile, build.sh, build.bat)

## Step 6: Update README with Team Info

1. Edit README.md on GitHub or locally
2. Add your team member names in the "Team Members" section
3. Commit and push:

```bash
git add README.md
git commit -m "Add team member names"
git push
```

## Step 7: Create a Good README Display

Your README.md already has:
- ✓ Project title and description
- ✓ Feature list
- ✓ Algorithm documentation
- ✓ Build instructions
- ✓ Usage examples
- ✓ Technical details

Make sure to add:
- Your team member names
- Any additional notes or credits

## Step 8: Share with CCC

1. Copy your repository URL:
   ```
   https://github.com/YOUR_USERNAME/decentralized-trading-terminal
   ```

2. Share this URL with CCC according to their submission instructions

## Optional: Add Screenshots

If you want to add screenshots to your README:

1. Run the terminal and take screenshots
2. Create an `images/` folder in your repository
3. Add screenshots to the folder
4. Reference them in README.md:
   ```markdown
   ![Terminal Screenshot](images/screenshot.png)
   ```

## Git Commands Reference

### Basic Commands
```bash
# Check status
git status

# Add files
git add <filename>
git add .  # Add all files

# Commit changes
git commit -m "Your message"

# Push to GitHub
git push

# Pull from GitHub
git pull
```

### Branching (Optional)
```bash
# Create new branch
git checkout -b feature-name

# Switch branches
git checkout main

# Merge branch
git merge feature-name
```

### Viewing History
```bash
# View commit history
git log

# View changes
git diff
```

## Common Issues and Solutions

### Issue: "Permission denied (publickey)"
**Solution**: Use HTTPS instead of SSH, or set up SSH keys:
```bash
# Use HTTPS URL
git remote set-url origin https://github.com/YOUR_USERNAME/decentralized-trading-terminal.git
```

### Issue: "Repository not found"
**Solution**: Check the URL is correct and repository exists:
```bash
git remote -v  # View current remote
git remote set-url origin <correct-url>
```

### Issue: "Failed to push"
**Solution**: Pull first, then push:
```bash
git pull origin main --rebase
git push origin main
```

### Issue: Large files
**Solution**: Make sure obj/ folder is in .gitignore (it already is)

## .gitignore Verification

Your .gitignore should include:
```
# Compiled files
*.o
*.obj
*.exe
*.out

# Build directories
obj/
build/
bin/

# IDE files
.vscode/
.idea/

# OS files
.DS_Store
Thumbs.db
```

This is already set up in your project!

## Repository Structure on GitHub

Your repository should look like this:

```
decentralized-trading-terminal/
├── .gitignore
├── README.md
├── QUICKSTART.md
├── SETUP.md
├── USAGE_GUIDE.md
├── ALGORITHMS.md
├── ARCHITECTURE.md
├── PROJECT_REPORT.md
├── PROJECT_SUMMARY.txt
├── GITHUB_SETUP.md
├── Makefile
├── build.sh
├── build.bat
├── include/
│   ├── blockchain.h
│   ├── order_book.h
│   ├── terminal_ui.h
│   └── trading_algorithms.h
└── src/
    ├── blockchain.cpp
    ├── order_book.cpp
    ├── trading_algorithms.cpp
    ├── terminal_ui.cpp
    └── main.cpp
```

## Submission Checklist

Before submitting to CCC:

- [ ] Repository is public
- [ ] All source files are uploaded
- [ ] README.md has team member names
- [ ] Code compiles without errors
- [ ] Documentation is complete
- [ ] .gitignore is properly configured
- [ ] Repository URL is shared with CCC

## Tips for a Good Repository

1. **Clear README**: Your README should explain what the project does
2. **Good Commits**: Use descriptive commit messages
3. **Documentation**: Include all documentation files
4. **Clean Code**: Remove commented-out code and debug statements
5. **Test Build**: Make sure someone else can clone and build

## Example Commit Messages

Good commit messages:
- ✓ "Add greedy algorithm for best execution"
- ✓ "Implement DP portfolio optimization"
- ✓ "Fix order matching bug in price-time priority"
- ✓ "Update README with team member names"

Bad commit messages:
- ✗ "Update"
- ✗ "Fix"
- ✗ "Changes"
- ✗ "asdf"

## Collaboration with Team

If working with team members:

1. **Add Collaborators**:
   - Go to repository Settings
   - Click "Collaborators"
   - Add team member GitHub usernames

2. **Branching Strategy**:
   ```bash
   # Each member works on their own branch
   git checkout -b member-name-feature
   
   # Push their branch
   git push origin member-name-feature
   
   # Create pull request on GitHub
   # Review and merge to main
   ```

3. **Avoid Conflicts**:
   - Work on different files when possible
   - Pull before starting work
   - Communicate with team

## Final Steps

1. ✓ Create GitHub repository
2. ✓ Push all code
3. ✓ Add team member names
4. ✓ Verify everything is visible
5. ✓ Share URL with CCC
6. ✓ Submit before deadline (30th April 2026)

## Need Help?

- **Git Documentation**: https://git-scm.com/doc
- **GitHub Guides**: https://guides.github.com/
- **Git Tutorial**: https://www.atlassian.com/git/tutorials

---

**Good luck with your submission!** 🚀

Remember: The deadline is **30th April 2026**. Don't wait until the last minute!
