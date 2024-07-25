def Count(Motifs):
    count = {}  
    
    k = len(Motifs[0])

    for symbol in "ACGT":
        count[symbol] = []
        for j in range(k):
            count[symbol].append(0)

    t = len(Motifs)
    for i in range(t):
        for j in range(k):
            symbol = Motifs[i][j]
            count[symbol][j] += 1

    return count

def Profile(Motifs):
    t = len(Motifs)
    k = len(Motifs[0])
    profile = {}
    
    for symbol in 'ACGT':
        profile[symbol] = []
        for j in range(k):
            profile[symbol].append(0)
    
    for i in range(t):
        for j in range(k):
            symbol = Motifs[i][j]
            profile[symbol][j] += 1/k
            
    return profile

def Consensus(Motifs):
    k = len(Motifs[0])
    count = Count(Motifs)
    consensus = ""
    for j in range(k):
        m = 0
        frequentSymbol = ""
        for symbol in "ACGT":
            if count[symbol][j] > m:
                m = count[symbol][j]
                frequentSymbol = symbol
        consensus += frequentSymbol
    return consensus

def Score(Motifs):
    consensus = Consensus(Motifs) 
    k = len(consensus)
    t = len(Motifs)
    score = 0

    for j in range(k):
        for i in range(t):
            if Motifs[i][j] != consensus[j]:
                score += 1

    return score

def Pr(text, profile):
    probability = 1.0

    for i in range(len(text)):
        nucleotide = text[i]
        probability *= profile[nucleotide][i]

    return probability

def ProfileMostProbableKmer(text, k, profile):
    max_probability = -1.0  
    most_probable_kmer = ""

    for i in range(len(text) - k + 1):
        kmer = text[i:i+k]
        probability = Pr(kmer, profile)  

        if probability > max_probability:
            max_probability = probability
            most_probable_kmer = kmer

    return most_probable_kmer

def GreedyMotifSearch(Dna, k, t):
    n = len(Dna[0])
    best_motifs = [Dna[i][0:k] for i in range(t)]

    for i in range(n - k + 1):
        motifs = [Dna[0][i:i+k]]
        for j in range(1, t):
            profile = Profile(motifs[0:j])
            motifs.append(ProfileMostProbableKmer(Dna[j], k, profile))

        if Score(motifs) < Score(best_motifs):
            best_motifs = motifs

    return best_motifs

def CountWithPseudocounts(Motifs):
    count = {symbol: [1] * len(Motifs[0]) for symbol in "ACGT"}
    for i in range(len(Motifs)):
        for j in range(len(Motifs[i])):
            symbol = Motifs[i][j]
            count[symbol][j] += 1
    return count

def ProfileWithPseudocounts(Motifs):
    t = len(Motifs) + 4
    count = CountWithPseudocounts(Motifs)
    profile = {symbol: [float(c) / t for c in count[symbol]] for symbol in "ACGT"}
    return profile

def ScoreWithPseudocounts(Motifs):
    count = CountWithPseudocounts(Motifs)
    score = 0
    for j in range(len(Motifs[0])):
        max_count = max(count[symbol][j] for symbol in "ACGT")
        score += sum(count[symbol][j] for symbol in "ACGT") - max_count
    return score

def ProfileMostProbablePattern(Text, k, profile):
    max_prob = -1
    most_probable = ""
    for i in range(len(Text) - k + 1):
        pattern = Text[i:i+k]
        prob = 1
        for j in range(k):
            prob *= profile[pattern[j]][j]
        if prob > max_prob:
            max_prob = prob
            most_probable = pattern
    return most_probable

def GreedyMotifSearchWithPseudocounts(Dna, k, t):
    BestMotifs = [string[:k] for string in Dna]
    
    for i in range(len(Dna[0]) - k + 1):
        Motifs = [Dna[0][i:i+k]]
        
        for j in range(1, t):
            profile = ProfileWithPseudocounts(Motifs)
            motif = ProfileMostProbablePattern(Dna[j], k, profile)
            Motifs.append(motif)
        
        if ScoreWithPseudocounts(Motifs) < ScoreWithPseudocounts(BestMotifs):
            BestMotifs = Motifs
    
    return BestMotifs

def RandomMotifs(dna,k,t):

    kmm = []
    sc = []
    D = {}
    for i in range(0,len(dna)):
        km = []
        for kk in range(len(dna[i])-k+1):
            km += [dna[i][kk:kk+k]]
        D[i] = km
    for m in range(0,t):
        ran = random.randint(0,len(D[0])-1)
        kmm += [D[m][ran]]

    return kmm

def Normalize(Probabilities):
    total_probability = sum(Probabilities.values())  # Calculate the sum of all probabilities
    
    # Normalize each probability by dividing by the total probability
    normalized_probabilities = {key: value / total_probability for key, value in Probabilities.items()}
        
    return normalized_probabilities

import random

def WeightedDie(Probabilities):
    # Generate a random number between 0 and 1
    p = random.uniform(0, 1)
    
    # Iterate through k-mers and their probabilities
    for kmer, probability in Probabilities.items():
        p -= probability
        if p <= 0:
            return kmer

def ProfileGeneratedString(Text, profile, k):
    n = len(Text)
    probabilities = {}
    for i in range(0, n - k + 1):
        kmer = Text[i:i+k]
        probabilities[kmer] = Pr(kmer, profile)
    probabilities = Normalize(probabilities)  # Normalize the probabilities
    return WeightedDie(probabilities)

def GibbsSampler(Dna, k, t, N):
    Motifs=RandomMotifs(Dna, k, t)
    BestMotifs=Motifs
    for j in range(N):
        i=random.randint(1,t)
        text=Motifs.pop(i-1)
        profile=ProfileWithPseudocounts(Motifs)
        kmer=ProfileMostProbableKmer(text, k, profile)
        Motifs.insert(i-1,kmer)
        if Score(Motifs)<Score(BestMotifs):
            BestMotifs=Motifs
    return BestMotifs