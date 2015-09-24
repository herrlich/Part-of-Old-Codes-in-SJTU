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

import sys, os, lucene, threading, time,chardet,urllib2,re
from datetime import datetime
from BeautifulSoup import BeautifulSoup
from ctypes import *
import urllib
import Queue
import urlparse

#这个程序只适用于在魔法桌面上爬取的网站http://www.ommoo.com/别的网站还要改搜索的标签#

"""
This class is loosely based on the Lucene (java implementation) demo class
org.apache.lucene.demo.IndexFiles.  It will take a directory as an argument
and will index all of the files in that directory and downward recursively.
It will index on the file path, the file name and the file contents.  The
resulting Lucene index will be placed in the current directory and called
'index'.
"""

class Ticker(object):

    def __init__(self):
        self.tick = True

    def run(self):
        while self.tick:
            sys.stdout.write('.')
            sys.stdout.flush()
            time.sleep(1.0)

class IndexFiles(object):
    """Usage: python IndexFiles <doc_directory>"""

    def __init__(self, root, storeDir, analyzer):

        if not os.path.exists(storeDir):
            os.mkdir(storeDir)
        store = lucene.SimpleFSDirectory(lucene.File(storeDir))
        writer = lucene.IndexWriter(store, analyzer, True,
                                    lucene.IndexWriter.MaxFieldLength.LIMITED)
        writer.setMaxFieldLength(1048576)
        self.indexDocs(root, writer)
        ticker = Ticker()
        print 'optimizing index',
        threading.Thread(target=ticker.run).start()
        writer.optimize()
        writer.close()
        ticker.tick = False
        print 'done'

    def indexDocs(self, root, writer):
        for root, dirnames, filenames in os.walk(root):
            for filename in filenames:
                if filename.endswith('.txt'):
                    continue
                print "adding", filename
                try:
                    path = os.path.join(root, filename)
                    file = open(path)
                    buf = file.read()
                    contents=buf
                    result = chardet.detect(buf)['encoding']
                    if result=='GB2312':
                        contents = buf.decode('gbk').encode('utf8')
                    file.close()
                    soup=BeautifulSoup(contents)
                    url=mydict[filename]
                    proto, rest = urllib.splittype(url)
                    site, rest = urllib.splithost(rest)
                    title=str(soup.head.title.string.strip()).decode('utf8')
                    flag2=0
                    for i in soup.findAll('img'):
                        contents=""
                        flag1=0
                        flag3=0
                        try:
                            contents=contents+' '+i['alt']
                        except:
                            pass
                        tempurl=i['src']
                        imgurl=urlparse.urljoin(url,tempurl)
                        temp=i.parent.parent
                        try:
                            photoid=temp.find('a')['data-photo-id']
                            flag1=1
                        except:
                            pass
                        try:
                            picid=temp.parent.find('article')['id']
                            flag3=1
                        except:
                            pass
                        try:
                            for t in temp.findAll('b'):
                                try:
                                    contents=contents+' '+t.string.strip()
                                except:
                                    pass
                        except:
                            pass
                        try:
                            for k in temp.findAll('p'):
                                try:
                                    contents=contents+' '+k.string.strip()
                                except:
                                    pass
                        except:
                            pass
                        try:
                            for j in temp.findAll('span',{'class':'title'}):
                                try:
                                    contents=contents+' '+j.string.strip()
                                except:
                                    pass
                        except:
                            pass
                        if flag1==1:
                            timetowait=0
                            try:
                                for p in temp.parent.findAll('div',{'class':'card-content'}):
                                    if timetowait<flag2:
                                        timetowait+=1
                                        continue
                                    contents=contents+' '+p.string.strip()
                                    flag2+=1
                                    break
                            except:
                                pass
                        if flag3==1:
                            try:
                                for q in temp.parent.findAll('div',{'class':'post-title'}):
                                    r=q.find('h1')
                                    contents=contents+' '+str(r.string).decode('utf8')
                                    break
                            except:
                                pass
                        contents=contents.strip()
                        doc = lucene.Document()
                        doc.add(lucene.Field("imgurl", imgurl,
                                            lucene.Field.Store.YES,
                                            lucene.Field.Index.NOT_ANALYZED))
                        doc.add(lucene.Field("url", url,
                                            lucene.Field.Store.YES,
                                            lucene.Field.Index.NOT_ANALYZED))
                        doc.add(lucene.Field("title", title,
                                            lucene.Field.Store.YES,
                                            lucene.Field.Index.NOT_ANALYZED))
                        if len(contents) > 0:
                            dll=cdll.LoadLibrary("F:\\ICTCLAS50_Windows_32_C\ICTCLAS50.dll")
                            dll.ICTCLAS_Init(c_char_p("F:\\ICTCLAS50_Windows_32_C"))
                            strlen = len(c_char_p(contents).value)
                            t =c_buffer(strlen*6)
                            bSuccess = dll.ICTCLAS_ParagraphProcess(c_char_p(contents),c_int(strlen),t,c_int(0),0)
                            contents=t.value.decode('gbk').encode('utf8')
                            ##list=t.value.split()
                            ##print ' '.join(list)
                            dll.ICTCLAS_Exit()
                            doc.add(lucene.Field("contents", contents,
                                                lucene.Field.Store.NO,
                                                lucene.Field.Index.ANALYZED))
                        else:
                            print "warning: no content in part of %s" % filename
                        writer.addDocument(doc)
                except Exception, e:
                    print "Failed in indexDocs:", e

if __name__ == '__main__':
##    if len(sys.argv) < 2:
##        print IndexFiles.__doc__
##        sys.exit(1)
    lucene.initVM()
    print 'lucene', lucene.VERSION
    start = datetime.now()
    dic= open('F:\\html\index.txt')
    d = dic.readlines()
    dic.close()
    mydict = {}
    for word in d:
        key = word.split(';')[0]
        value = word.split(';')[1]
        mydict[key] = value
    try:
##        IndexFiles(sys.argv[1], "index", lucene.WhitespaceAnalyzer(lucene.Version.LUCENE_CURRENT))
        IndexFiles('F:\\html', "F:\\imgindex", lucene.WhitespaceAnalyzer(lucene.Version.LUCENE_CURRENT))
        end = datetime.now()
        print end - start
    except Exception, e:
        print "Failed: ", e
