def PatternMatching(Pattern, Genome):
    positions = []  # Output variable
    Pattern_length = len(Pattern)
    Genome_length = len(Genome)

    for i in range(Genome_length - Pattern_length + 1):
        if Genome[i:i + Pattern_length] == Pattern:
            positions.append(i)

    return positions