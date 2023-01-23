import os

filesExtensions = [".hpp", ".cpp"]
subfolderToCount = ["."]
subFolderToIgnore = ["include", "doc", "examples", "lib", "x64", ".vs", ".git", "Assets"]

def main():
    CountLineOfCodes()

nbLines = 0
def CountLineOfCodes():
    global nbLines
    nbLines  = 0
    for p in subfolderToCount:
        if(os.path.exists(p) and not p in subFolderToIgnore):
            CountLineRecur(p)

    print("There are " + str(nbLines) + " lines of code in your directories!")



def CountLineRecur(path):
    directories = [d for d in os.listdir(path) if not os.path.isfile(path + "/" + d) and not d in subFolderToIgnore]
    files = [f for f in os.listdir(path) if os.path.isfile(path + "/" + f)]

    for file in files:
        AddLines(path + "/" + file)
    
    for directory in directories:
        CountLineRecur(path + "/" + directory)
    

def AddLines(fileName:str):
    global nbLines
    for ext in filesExtensions:
        if fileName.endswith(ext):
            print("Counting lines of : " + fileName)
            file = open(fileName, 'r')
            while file.readline():
                nbLines += 1
            file.close
            break

if __name__ == "__main__":
    main()