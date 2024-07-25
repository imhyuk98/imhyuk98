def ReverseComplement(Pattern):
    Pattern = Reverse(Pattern) # reverse all letters in a string
    Pattern = Complement(Pattern) # complement each letter in a string
    return Pattern

def Reverse(Pattern):
    rev = ""
    for char in Pattern:
        rev = char + rev
    return rev

def Complement(Pattern):
    comp = ""
    for char in Pattern:
        if char == "A":
            char = char.replace("A","T")
        elif char == "C":
            char = char.replace("C","G")
        elif char == "G":
            char = char.replace("G","C")
        elif char == "T":
            char = char.replace("T","A")
        comp += char
    return comp

def PatternMatching(Pattern, Genome):
    positions = []  # Output variable
    Pattern_length = len(Pattern)
    Genome_length = len(Genome)

    for i in range(Genome_length - Pattern_length + 1):
        if Genome[i:i + Pattern_length] == Pattern:
            positions.append(i)

    return positions