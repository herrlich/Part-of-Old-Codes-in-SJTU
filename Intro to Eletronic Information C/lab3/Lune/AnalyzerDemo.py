import os, sys, lucene
lucene.initVM()

sys.path.append(os.path.dirname(os.path.abspath(sys.argv[0])))
sys.path.append("F:\\LuceneInAction")
from lia.analysis.AnalyzerDemo import AnalyzerDemo
AnalyzerDemo.main(sys.argv)

"""这里先将那个文件的路径加入sys，然后再引用的。"""