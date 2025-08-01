#!/bin/bash

COMMIT_MESSAGE=$(cat $1)
PATTERN="(fix|feat|refacto|style|docs|chore|perf|test|build|ci)!?: .{1,}"

if ! echo "$COMMIT_MESSAGE" | grep -Eq "$PATTERN"; then
  echo "Bad format commit" >&2
  echo "<type>[optional scope]: <description>" >&2
  exit 1
fi
exit 0
