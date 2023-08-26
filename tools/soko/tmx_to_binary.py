import tkinter as tk
from tkinter import filedialog
from xml.dom.minidom import parse,parseString


root = tk.Tk()
root.withdraw()

file_path = filedialog.askopenfilename()

print(file_path)

document = parse(file_path)

mapHeaderWidth = int(document.getElementsByTagName("map")[0].attributes.getNamedItem("width").nodeValue)
print(mapHeaderWidth)
mapHeaderHeight = int(document.getElementsByTagName("map")[0].attributes.getNamedItem("height").nodeValue)
print(mapHeaderHeight)
dataText = document.getElementsByTagName("data")[0].firstChild.nodeValue
print(dataText)
scrub = "".join(dataText.split()) #Remove all residual whitespace in data block
scrub2 = [int(i) for i in scrub.split(",")] #Convert all tileIDs to int.
print(scrub)
print(scrub2)
scrub3 = list([mapHeaderWidth,mapHeaderHeight]) + scrub2
print(scrub3)
rawBytes = bytearray(scrub3)
rawBytesImmut = bytes(rawBytes)
outfile_path = "".join([file_path.split(".")[0],".bin"])
print(outfile_path)
with open(outfile_path,"wb") as binary_file:
    binary_file.write(rawBytesImmut)
