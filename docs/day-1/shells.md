# UNIX Shells

The UNIX Shell extends the command line environment.

There are various shells. A few of them are:

1. Bourne Shell (sh)
1. Bourne Again Shell (bash)
1. Korn Shell (ksh)
1. Restricted Korn Shell (rksh)
1. C Shell (csh)

Some of the common features provided by shells are:

1. Command substitution
1. Job control
1. Piping
1. Condition testing
1. Loops
1. Spell checking

## How to deny interactive shell access to a user?

Set the shell for that user's account to /bin/false

```
usermod -s /bin/false <user id>
```