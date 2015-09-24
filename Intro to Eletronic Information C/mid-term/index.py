#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      admin
#
# Created:     25/10/2012
# Copyright:   (c) admin 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python


# -*- coding: utf-8 -*-


import sys, os, lucene, threading, time,chardet,urllib2
from datetime import datetime
from BeautifulSoup import BeautifulSoup
from ctypes import *
import re
import string
##过滤HTML中的标签
#将HTML中标签等信息去掉
#@param htmlstr HTML字符串?

def filter_tags(htmlstr):#先过滤CDATA
    re_cdata=re.compile('//<!\[CDATA\[[^>]*//\]\]>',re.I) #匹配CDATA
    re_script=re.compile('<\s*script[^>]*>[^<]*<\s*/\s*script\s*>',re.I)#Script
    re_style=re.compile('<\s*style[^>]*>[^<]*<\s*/\s*style\s*>',re.I)#style
    re_br=re.compile('<br\s*?/?>')#处理换行
    re_h=re.compile('</?\w+[^>]*>')#HTML标签
    re_comment=re.compile('<!--[^>]*-->')#HTML注释
    s=re_cdata.sub('',htmlstr)#去掉CDATA
    s=re_script.sub('',s) #去掉SCRIPT
    s=re_style.sub('',s)#去掉style
    s=re_br.sub('\n',s)#将br转换为换行?
    s=re_h.sub('',s) #去掉HTML 标签
    s=re_comment.sub('',s)#去掉HTML注释#去掉多余的空行?
    blank_line=re.compile('\n+')
    s=blank_line.sub('\n',s)
    s=replaceCharEntity(s)#替换实体
    return s
    ##替换常用HTML字符实体.
    #使用正常的字符替换HTML中特殊的字符实体.
    #你可以添加新的实体字符到CHAR_ENTITIES中?处理更多HTML字符实体.
    #@param htmlstr HTML字符串。


def replaceCharEntity(htmlstr):
    CHAR_ENTITIES={'nbsp':' ','160':' ','lt':'<','60':'<','gt':'>','62':'>','amp':'&','38':'&','quot':'"','34':'"',}
    re_charEntity=re.compile(r'&#?(?P<name>\w+);')
    sz=re_charEntity.search(htmlstr)
    while sz:
        entity=sz.group()#entity全称，如&gt;
        key=sz.group('name')#去除&;后entity,如&gt;为gt
        try:
            htmlstr=re_charEntity.sub(CHAR_ENTITIES[key],htmlstr,1)
            sz=re_charEntity.search(htmlstr)
        except KeyError:#以空串代替
            htmlstr=re_charEntity.sub('',htmlstr,1)
            sz=re_charEntity.search(htmlstr)
    return htmlstr


def repalce(s,re_exp,repl_string):
    return re_exp.sub(repl_string,s)


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
                    title=str(soup.head.title.string).decode('utf8')
                    new_contents=filter_tags(contents)
                    new_contents=str(new_contents).strip().decode('utf8')
                    pos=new_contents.find('>')
                    new_contents=new_contents[pos+1:]#删除前面的?<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
                    temp=new_contents.split()
                    newtext=' '.join(temp)
                    contents=''.join(soup.findAll(text=True))
                    doc = lucene.Document()
                    doc.add(lucene.Field("text", newtext,
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
                        print "warning: no content in %s" % filename
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
        value=''
        try:
            key = word.split(';')[0]
            value = word.split(';')[1]
            mydict[key] = value
        except:
            pass
    try:
##        IndexFiles(sys.argv[1], "index", lucene.SimpleAnalyzer(lucene.Version.LUCENE_CURRENT))
        IndexFiles('F:\\html', "F:\\index", lucene.SimpleAnalyzer(lucene.Version.LUCENE_CURRENT))
        end = datetime.now()
        print end - start
    except Exception, e:
        print "Failed: ", e
