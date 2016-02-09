About
=====

Added Enhanced Bilingual Evaluation Understudy (BLEU) in EBLEU folder, which is more precise when evaluating  morphologically rich languages.

Consideration of Synonyms
=====

In our enhanced metric, we would like to reward matches of synonyms, since the correct
meaning is still conveyed.
Consider this test phrase: "this is a exam" and this reference phrase: "this is a quiz"
The BLEU score is calculated as follows:
BLEU = (1+1+1+0)/4 = 3/4 = 0.75
BLEU does not count the word "exam" as a match, because it does not find it in the reference
phrase. However, this word is not a bad choice. In our method, we want to score the synonym
“exam” higher than zero and lower than the exact word "quiz".
To do this, for each word in a test phrase we try to find its synonyms. We check for an exact
word match and for all test phrase synonyms to find the closest words to the reference.
We apply the default BLEU algorithm to the modified test phrase and reference phrase, with
one difference. The default BLEU algorithm scores this new test phrase as 1.0, but we know that
the original test phrase is "this is a exam". So, we would like to give a score higher than 0.75 but
less than 1.0 to the test phrase.
During the BLEU evaluation, we check each word for an exact match. If the word is a
synonym and not an exact match, we do not give a full score to that word. The score for a
synonym will be the default BLEU score for an original word multiplied by a constant (synonymscore).

For example, if this constant equals 0.90, the new score with synonyms is:
(1+1+1+0.9)/4 = 3.9/4 = 0.975
With this algorithm, we have synonym scores for all n-grams, because in 2-gram we have “a
quiz” and in 3-gram,”is a quiz” in both test and reference phrases.


Consideration of Rare Words
=====

Our algorithm gives extra points to rare word matches. First, it obtains the rare words found in
the reference corpus. If we sort all distinct words of the reference with their repetition order
(descending), the last words in this list are rare words. The algorithm takes a specific percentage
of the whole sorted list as the rare words (rare-words-percent).
When the default BLEU algorithm tries to score a word, if this word is in the rare word list,
the score is multiplied by a constant (rare-words-score). This action applies to all n-grams. So, if
we have a rare word in a 2-gram, the algorithm increases the score for this 2-gram. For example,
if the word "roman" is rare, the "roman empire" 2-gram gets an increased score. The algorithm is
careful that score of each sentence falls within the range of 0.0 and 1.0.

Determination of Cumulative Score
=====

The cumulative score of our algorithm combines default BLEU scores using logarithms and
exponentials as follows:

1. Initialize s = 0

2. For each ith-gram:
a. s = s + log(Bi)
b. Ci = exp(s / i)

where Bi is the default BLEU score and Ci is the cumulative score.
In addition, we know that:
exp log a + log b = a ∗ b
and:
exp log a /b = a^(de)

Final info
====

Feel free to use this tool if you cite:
Wołk K., Marasek K., “Enhanced Bilingual Evaluation Understudy”, Lecture Notes on Information Theory, ISSN: 2301-3788, 2014

For more information, see: http://arxiv.org/pdf/1509.09088

For any questions:
| Krzysztof Wolk
| krzysztof@wolk.pl
