import os, sys, lucene
lucene.initVM()

sys.path.append(os.path.dirname(os.path.abspath(sys.argv[0])))
sys.path.append("F:\\LuceneInAction")
from lia.analysis.AnalyzerDemo import AnalyzerDemo
AnalyzerDemo.main(sys.argv)

"""�����Ƚ��Ǹ��ļ���·������sys��Ȼ�������õġ�"""