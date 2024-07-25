def FrequencyMap(Text, k):
    freq = {}
    n = len(Text)
    for i in range(n - k + 1):
        kmer = Text[i:i + k]
        if kmer in freq:
            freq[kmer] += 1
        else:
            freq[kmer] = 1
    return freq