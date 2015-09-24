#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      admin
#
# Created:     13/09/2012
# Copyright:   (c) admin 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python

# -*- coding: utf-8 -*-


from lucene import \
    QueryParser, IndexSearcher, WhitespaceAnalyzer, SimpleFSDirectory, File, \
    VERSION, initVM, Version, BooleanQuery, BooleanClause
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

def parseCommand(command):
    '''
    input: C title:T author:A language:L
    output: {'contents':C, 'title':T, 'author':A, 'language':L}

    Sample:
    input:'contenance title:henri language:french author:william shakespeare'
    output:{'author': ' william shakespeare',
                   'language': ' french',
                   'contents': ' contenance',
                   'title': ' henri'}
    '''
    allowed_opt = ['site']
    command_dict = {}
    opt = 'contents'
    for i in command.split(' '):
        if ':' in i:
            opt, value = i.split(':')[:2]
            opt = opt.lower()
            if opt in allowed_opt and value != '':
                command_dict[opt] = command_dict.get(opt, '') + ' ' + value
        else:
            command_dict[opt] = command_dict.get(opt, '') + ' ' + i
    return command_dict


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

        command_dict = parseCommand(command)
        querys = BooleanQuery()
        for k,v in command_dict.iteritems():
            query = QueryParser(Version.LUCENE_CURRENT, k,
                                analyzer).parse(v)
            querys.add(query, BooleanClause.Occur.MUST)
        scoreDocs = searcher.search(querys, 50).scoreDocs
        print "%s total matching documents." % len(scoreDocs)

        for scoreDoc in scoreDocs:
            doc = searcher.doc(scoreDoc.doc)
##            explanation = searcher.explain(query, scoreDoc.doc)
            print "------------------------"
            print 'path:', doc.get("path")
            print 'name:', doc.get("name")
            print 'title:', doc.get('title')
            print 'url:', doc.get('url')
##            print explanation


if __name__ == '__main__':
    STORE_DIR = "F:\\index"
    initVM()
    print 'lucene', VERSION
    directory = SimpleFSDirectory(File(STORE_DIR))
    searcher = IndexSearcher(directory, True)
    analyzer = WhitespaceAnalyzer(Version.LUCENE_CURRENT)
    run(searcher, analyzer)
    searcher.close()
