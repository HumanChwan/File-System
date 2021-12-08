# FILE SYSTEM

## Accepted Commands:

- `cd`:
  - Usage: `cd <...path...>`
  - Moves the terminal to direct to a directory.
- `touch`:
  - Usage: `touch [...files]`
  - Creates new file in the relative path.
- `mkdir`:
  - Usage: `mkdir [...files]`
  - Creates new directories in the relative path.
- `rm`:
  - Usage: `rm [-d/-r] [...files]`
  - Removes nodes from the relative path.
- `ls`:
  - Usage: `ls [-a] <...path...>`
  - Shows the Node list from the relative path.
- `cat`:
  - Usage: `cat < [...in...] > [...out...]`
  - Manipulates the content of file(s) from the relative path.
- `tree`:
  - Usage: `tree <...path...>`
  - Shows the tree of nodes of the relative path.
- `clear`:
  - Usage: `clear`
  - Clears the terminal.
- `exit`:
  - Usage: `exit`
  - Exits the application.


## How to run:

- change the permissions of the `run.sh` file by running to make it executable:
  - `chmod +x run.sh`
- before running the application, make sure you a `.env` file in your root folder.
- Inside `.env` make sure to have a single numeric Integer value (0 < x < 2^31).
- The Integer inside the `.env` file is the secret key to for storing your passwords (XOR).
- Run the application by executing the following command:
  - `./run.sh`