Command-Line Line Editor — Help
Overview

This help file explains all commands supported by the Command-Line Line Editor and provides an example of how to use each command.

1. Enter Text

Purpose:
Allows the user to enter text into the editor.

Usage:

Enter your choice: 1
Enter text:
Hello, this is my first line.
This is my second line.

The entered text becomes the current content of the editor.

2. Display Text

Purpose:
Displays the text currently stored in the editor.

Usage:

Enter your choice: 2

Example output:

Current Text:
Hello, this is my first line.
This is my second line.
3. Find and Replace

Purpose:
Searches for a word or phrase and replaces it with another word or phrase.

Usage:

Enter your choice: 3
Enter text to find: first
Enter replacement text: main

Example:

Before:

Hello, this is my first line.

After:

Hello, this is my main line.
4. Undo Last Action

Purpose:
Reverts the most recent editing operation.

Usage:

Enter your choice: 4

Example:

Before undo:

Hello, this is my main line.

After undo:

Hello, this is my first line.

If there is no previous action to undo, the editor displays an appropriate message.

5. Word and Line Count

Purpose:
Counts the number of words and lines in the current text.

Usage:

Enter your choice: 5

Example output:

Number of lines: 2
Number of words: 10
6. Exit

Purpose:
Closes the line editor.

Usage:

Enter your choice: 6

Example output:

Exiting Line Editor...
Thank you!
