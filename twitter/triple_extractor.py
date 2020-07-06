import re
from stanfordcorenlp import StanfordCoreNLP
from openie import StanfordOpenIE

class TripleExtractor():
    def __init__(self):
        # self.nlp = StanfordCoreNLP('../../stanford-corenlp-4.0.0/', memory='8g')
        # self.nlp.ner("init")
        self.regex_pattern = r'[^\x00-\x7F]+' 
        self.openie = StanfordOpenIE()

    def clean_text(self, text):
        return  re.sub(self.regex_pattern, ' ', text)

    def extract_entities(self, text):
        return self.nlp.ner(text)

    def get_triples(self, text):
        triples = self.openie.annotate(text)
        return triples
