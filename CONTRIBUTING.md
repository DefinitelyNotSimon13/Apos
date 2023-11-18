# Contributing to Apos - Database Manager

Thank you for considering contributing to Apos – Database Manager. It is
people like you that make Apos—Database Manager such a great tool.

## Where do I go from here?

If you've noticed a bug or have a feature request, make one! It is generally
best if you get confirmation of your bug or approval for your feature request
this way before starting to code.

## Fork & create a branch

If this is something you think you can fix, then fork and create a branch with
a descriptive name. A good branch name would be (where issue #325 is the
ticket you're working on):

```bash
git checkout -b 325-add-japanese-translations
```

## Get the test suite running

Make sure you're using the latest version of Node.js and npm. Install the
project's dependencies:

```bash
npm install
```

Run the test suite to ensure everything is working correctly:

```bash
npm test
```

## Implement your fix or feature

At this point, you're ready to make your changes! Feel free to ask for help;
everyone is a beginner at first.

## Make a Pull Request

At this point, you should switch back to your main branch and make sure it is
up to date with the latest code from the main repository:

```bash
git remote add upstream git@github.com:DefinitelyNotSimon13/Apos.git
git checkout main
git pull upstream main
```

Then update your feature branch from your local copy of main, and push it!

```bash
git checkout 325-add-japanese-translations
git rebase main
git push --set-upstream origin 325-add-japanese-translations
```

Go to the Apos – Database Manager repository and create a new Pull Request.
Fill out the form and wait for the approval!

## Keeping your Pull Request updated

If a maintainer asks you to “rebase” your PR, they're saying that a lot of
code has changed, and that you need to update your branch, so it's easier to
merge.

To learn more about rebasing in Git, there are a lot of
[good](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)
[resources](https://www.atlassian.com/git/tutorials/merging-vs-rebasing)
but here's the suggested workflow:

```bash
git checkout 325-add-japanese-translations
git pull --rebase upstream main
git push --force-with-lease 325-add-japanese-translations
```

## Merging a PR (maintainers only)

A PR can only be merged into main by a maintainer if:

- It is passing CI.
- It has been approved by at least two maintainers. If it was a maintainer who
  opened the PR, only one extra approval is needed.
- It has no requested changes.
- It is up to date with the current main.

Any maintainer is allowed to merge a PR if these conditions are met.

This `CONTRIBUTING.md` file provides a guide for contributors on how to create a branch, run the test suite, implement
a fix or feature, make a pull request, and keep a pull request updated. It also provides instructions for
maintainers on how to merge a pull request.