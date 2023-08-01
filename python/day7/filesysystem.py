import random

class File():

    def __init__(self, name: str, size: int):
        self.name: str = name
        self.size: int = size

class Directory():

    def __init__(self, name: str, parent):
        self.name:      str = name
        self.size:      int = 0
        self.parent:    Directory = parent
        self.children:  dict[str, File|Directory] = {}

class FS():

    def __init__(self):
        # Create root directory
        self.root:          Directory = Directory('root', None)
        self.pwd:           Directory = self.root
        self.all_dirs:      dict[str, Directory] = {'root': self.root}
        self.total_space:   int = 70_000_000

    def calculate_space(self):

        self.used_space: int = self.root.size
        self.free_space: int = self.total_space - self.used_space

        return self.free_space

    def calculate_directory_sizes(self, dir: Directory) -> int:

        '''
        Recursivly calculates the size of the directory and all its children.
        Updates the size attribute for both the passed directory and all child directories.

            Parameters:
                dir (Directory): A Directory Object that exists in within the FS() object

            Returns:
                size (int): Size of the Directory
        '''

        size = 0

        for child in dir.children.values():
            if isinstance(child, Directory) and child.size == 0:
                size += self.calculate_directory_sizes(child)
            elif isinstance(child, File) or (isinstance(child, Directory) and child.size != 0):
                size += child.size

        dir.size = size

        return size

    def _generate_id(self) -> int:

        return hex(random.randint(0x10000000, 0xffffffff))

    def cd(self, cd_to: str) -> None:

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

        new_directory = Directory(name, self.pwd)
        self.pwd.children.setdefault(name, new_directory)
        self.all_dirs.setdefault(self._generate_id(), new_directory)

    def create_file(self, name: str, size: int) -> None:  
        
        new_file = File(name, size)
        self.pwd.children.setdefault(name, new_file)