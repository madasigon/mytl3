from git import Repo

git = Repo('./').git

print(git.status())
print(git.is_dirty())