# Input:  A String Genome
# Output: The skew array of Genome as a list.
def SkewArray(Genome):
    # your code here
    skew = [0] 
    n = len(Genome)
    for i in range(n):
        if Genome[i] == "C":
            skew.append(skew[i] - 1)
        elif Genome[i] == "G":
            skew.append(skew[i] + 1)
        else:
            skew.append(skew[i])
    return skew
