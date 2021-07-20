from git import Repo

r = Repo('./')

print(r.git.status())
print(r.is_dirty())