def ApproximatePatternCount(Pattern, Text, d):
    count = 0
    for i in range(len(Text)-len(Pattern)+1):
        if HammingDistance(Pattern, Text[i:i+len(Pattern)]) <= d:
            count+=1
    return count