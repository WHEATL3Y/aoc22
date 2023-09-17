import random
import sys

class File:

    """A class to represent a file
    
    ...

    Attributes
    ----------
    name : str
        Name of the file
    size : int
        Size of the file

    Methods
    -------
    
    """

    def __init__(self, name: str, size: int):

        """
        Constructs all attributes for the File object
        
        Parameters
        ----------
            name : str
                Name of the file
            size : int
                Size of the file
        """

        self.name: str = name
        self.size: int = size

class Directory:

    """
    A class to represent a directory

    ...

    Attributes
    ----------
    name : str
        Name of the directory
    size : int
        Size of the directory
    parent : Directory
        Parent directory
    children : dict
        A dictionary of child objects in the directory

    Methods
    -------

    """

    def __init__(self, name: str, parent):

        """
        Constructs all necessary attributes for the Directory object

        Parameters
        ----------
            name : str
                Name of the directory
            size : int
                Size of the directory
            parent : Directory
                Parent directory
            children : dict
                A dictionary of child objects in the directory           
        """

        self.name:      str = name
        self.size:      int = 0
        self.parent:    Directory = parent
        self.children:  dict[str, File|Directory] = {}

class FS:

    """
    A class to represent the filesystem

    ...

    Attributes
    ----------
    root : Directory
        The root directory
    pwd : Directory
        The present working directory
    all_dirs : dict
        All directories that exist in the file system
    total_space : int
        The total space of the entire file system

    Methods
    -------
    calculate_space():
        Returns the free space in the filesystem
    calculate_directory_sizes(dir):
        Recursivly calculates the size fo the current directory and all children
    _generate_id():
        Generates a random ID
    cd(cd_to):
        Changes directories
    create_directory(name):
        Creates a directory as a child to the current directory
    create_file(name, size):
        Creates a file as a child to the current directory
    """

    def __init__(self):
        
        """
        Constructs all necessary attributes for the FS() object

        Parameters
        ----------
            root : Directory
                The root directory
            pwd : Directory
                The present working directory
            all_dirs : dict
                All directories that exist in the file system
            total_space : int
                The total space of the entire file system
        """

        self.root:          Directory = Directory('root', None)
        self.pwd:           Directory = self.root
        self.all_dirs:      dict[str, Directory] = {'root': self.root}
        self.total_space:   int = 70_000_000

    def calculate_space(self) -> int:

        """Returns the available space in the filesystem"""

        self.used_space: int = self.root.size
        self.free_space: int = self.total_space - self.used_space

        return self.free_space

    def calculate_directory_sizes(self, dir: Directory) -> int:
        
        """
        Recursivly calculates the size of the directory and all its children.
        Updates the size attribute for both the passed directory and all child directories.

        Parameters
        ----------
        dir : Directory
            A Directory object that exists in within the FS() object

        Returns
        -------
        size : int
            Size of the Directory
        """

        size = 0

        for child in dir.children.values():
            if isinstance(child, Directory) and child.size == 0:
                size += self.calculate_directory_sizes(child)
            elif isinstance(child, File) or (isinstance(child, Directory) and child.size != 0):
                size += child.size

        dir.size = size

        return size

    def _generate_id(self) -> int:

        """Returns random hex 32 bit ID"""

        return hex(random.randint(0x10000000, 0xffffffff))

    def cd(self, cd_to: str) -> None:

        """
        Changes the active directory by modifying FS().pwd
        
        Parameters
        ----------
        cd_to : str 
            The directory to change to, also takes .. (parent), and / (root)

        Returns
        -------
        None
        """

        match cd_to:
            case '/':
                self.pwd = self.root
            case '..':
                if self.pwd.name == 'root':
                    pass
                else:
                    self.pwd = self.pwd.parent
            case other:
                if cd_to not in self.pwd.children:
                    print('No such directory')
                else:
                    self.pwd = self.pwd.children[cd_to]

    def create_directory(self, name: str) -> None:

        """
        Creates a Directory() object in the current directory
        
        Parameters
        ----------
        name : str
            Name of the new directory

        Returns
        -------
        None
        """

        new_directory = Directory(name, self.pwd)
        self.pwd.children.setdefault(name, new_directory)
        self.all_dirs.setdefault(self._generate_id(), new_directory)

    def create_file(self, name: str, size: int) -> None:  

        """
        Creates a new File() object in the current directory

        Parameters
        ----------
        name : str
            Name of the file
        size : int
            Size of the file

        Returns
        -------
        None
        """
        
        new_file = File(name, size)
        self.pwd.children.setdefault(name, new_file)

def process_input(commands: list[str]) -> None:

    """
    Takes inputs and runs applicable functions
    
        Parameters:
            commands (list): List of commands

        Returns:
            None
    """

    def _command_handler(command: str) -> None:

        """
        Takes commands and runs applicable functions

            Parameters:
                commands (str): Command to process

            Returns:
                None
        """

        match command[1]:
            case 'cd':
                filesystem.cd(line[2])
            case 'ls':
                for k, v in filesystem.pwd.children.items():
                    if isinstance(v, Directory):
                        print(f'{v.size} dir {k}')
                    else:
                        print(f'{v.size} {k}')
            case 'pwd':
                print(filesystem.pwd.name)
            case 'exit' | 'quit':
                sys.exit(0)
            case other:
                print(f'Invalid Command: {line[1]}')

    for line in commands:

        line = line.strip().split(' ')

        match line[0]:
            case '$':
                _command_handler(line)
            case 'dir':
                filesystem.create_directory(line[1])
            case other:
                filesystem.create_file(line[1], int(line[0]))

def aoc() -> tuple[int, int]:

    """Returns the answers to advent of code questions"""

    # fs_object can either be File() or Directory() object
    aoc_criteria_dirs: list = [
        fs_object.size for fs_object in filesystem.all_dirs.values() if fs_object.size <= 100_000
        ]
    deletion_candidates: list = [
        fs_object.size for fs_object in filesystem.all_dirs.values() if fs_object.size > (30_000_000 - filesystem.calculate_space())
        ]

    return (sum(aoc_criteria_dirs), min(deletion_candidates))

def interactive_shell() -> None:

    """Asks for commands, passes to process_input()"""

    if (command := input('$ ')):
        process_input([f'$ {command}',])

if __name__ == '__main__':

    with open('input.txt', 'r') as input_file:
        input_file = input_file.readlines()

    filesystem = FS()
    process_input(input_file)
    filesystem.calculate_directory_sizes(filesystem.root)

    # For Advent of code answers
    print(aoc())

    # For interactive 'pseudo-shell'
    while True:
        interactive_shell()
