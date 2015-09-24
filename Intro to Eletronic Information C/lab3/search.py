from lucene import \
    QueryParser, IndexSearcher, SimpleAnalyzer, SimpleFSDirectory, File, \
    VERSION, initVM, Version
from ctypes import *


"""
This script is loosely based on the Lucene (java implementation) demo class
org.apache.lucene.demo.SearchFiles.  It will prompt for a search query, then it
will search the Lucene index in the current directory called 'index' for the
search query entered against the 'contents' field.  It will then display the
'path' and 'name' fields for each of the hits it finds in the index.  Note that
search.close() is currently commented out because it causes a stack overflow in
some cases.
"""
def run(searcher, analyzer):
    while True:
        print
        print "Hit enter with no input to quit."
        command = raw_input("Query:")
        if len(command) > 0:
            dll=cdll.LoadLibrary("F:\\ICTCLAS50_Windows_32_C\ICTCLAS50.dll")
            dll.ICTCLAS_Init(c_char_p("F:\\ICTCLAS50_Windows_32_C"))
            strlen = len(c_char_p(command).value)
            t =c_buffer(strlen*6)
            bSuccess = dll.ICTCLAS_ParagraphProcess(c_char_p(command),c_int(strlen),t,c_int(0),0)
            command=t.value.decode('gbk').encode('utf8')
            ##list=t.value.split()
            ##print ' '.join(list)
            dll.ICTCLAS_Exit()
            command=command.decode('utf8')
        if command == '':
            return
        print
        print "Searching for:", command
        query = QueryParser(Version.LUCENE_CURRENT, "contents",
                            analyzer).parse(command)
        scoreDocs = searcher.search(query, 50).scoreDocs
        print "%s total matching documents." % len(scoreDocs)

        for scoreDoc in scoreDocs:
            doc = searcher.doc(scoreDoc.doc)
            print 'path:', doc.get("path"), 'title:', doc.get("title"), 'url:', doc.get("url"), 'name:', doc.get("name")


if __name__ == '__main__':
    STORE_DIR = "F:\\index"
    initVM()
    print 'lucene', VERSION
    directory = SimpleFSDirectory(File(STORE_DIR))
    searcher = IndexSearcher(directory, True)
    analyzer = SimpleAnalyzer(Version.LUCENE_CURRENT)
    run(searcher, analyzer)
    searcher.close()
