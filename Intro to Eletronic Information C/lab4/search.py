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

import web
from web import form
import urllib2
import os
from lucene import \
    QueryParser, IndexSearcher, SimpleAnalyzer, SimpleFSDirectory, File, \
    VERSION, initVM, Version
from ctypes import *
from jvm import vm_env

urls = (
    '/', 'index',
    '/s', 's'
)


render = web.template.render('templates') # your templates

login = form.Form(
    form.Textbox('keyword'),
    form.Button('Search'),
)

def func(command, searcher, analyzer):
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
    query = QueryParser(Version.LUCENE_CURRENT, "contents",analyzer).parse(command)
    scoreDocs = searcher.search(query, 50).scoreDocs
    total=len(scoreDocs)
    qtitle=[]
    qurl=[]
    qnew_text1=[]
    qnew_text2=[]
    q_query=[]
    new_query=str(query).replace ('contents:','').decode('utf8')
    if total==0:
        return command,qurl,qtitle,qnew_text1,qnew_text2,q_query,total
    for scoreDoc in scoreDocs:
        doc = searcher.doc(scoreDoc.doc)
        text=doc.get("text")
        new_text=str(text).decode('utf8')
        temp_query=new_query.replace(' ','')
        num=new_text.find(temp_query)
        query_len=len(temp_query)
        splited_query=new_query.split(' ')
        splitlen=len(splited_query)
        if (num!=-1):
            try:
                new_text1=str(new_text[num-30:num]).strip().decode('utf8','ignore')
                new_text2=str(new_text[num+query_len:num+30+query_len]).strip().decode('utf8','ignore')
            except:
                try:
                    new_text1=str(new_text[num-30:num]).strip().decode('utf8','ignore')
                    new_text2=""
                except:
                    try:
                        new_text1=""
                        new_text2=str(new_text[num+query_len:num+30+query_len]).strip().decode('utf8','ignore')
                    except:
                        new_text1=""
                        new_text2=""
            q_query.append(temp_query)
        else:
            for i in range(splitlen):
                parted_query=splited_query[i].decode('utf8')
                num=new_text.find(parted_query)
                if num==-1:
                    continue
                query_len=len(parted_query)
                try:
                    new_text1=str(new_text[num-30:num]).strip().decode('utf8','ignore')
                    new_text2=str(new_text[num+query_len:num+30+query_len]).strip().decode('utf8','ignore')
                except:
                    try:
                        new_text1=str(new_text[num-30:num]).strip().decode('utf8','ignore')
                        new_text2=""
                    except:
                        try:
                            new_text1=""
                            new_text2=str(new_text[num+query_len:num+30+query_len]).strip().decode('utf8','ignore')
                        except:
                            new_text1=""
                            new_text2=""
                q_query.append(parted_query)
                break
            if num==-1:
                total=total-1
                continue
        title=doc.get("title")
        url=doc.get("url")
        qurl.append(url)
        qtitle.append(title)
        qnew_text1.append(new_text1)
        qnew_text2.append(new_text2)
    return command,qurl,qtitle,qnew_text1,qnew_text2,q_query,total

class index:
    def GET(self):
        f = login()
        return render.formtest(f)

class s:
    def GET(self):
        vm_env = initVM()
        form1 = login()
        user_data = web.input()
        vm_env.attachCurrentThread()
        STORE_DIR = "F:\\index"
        directory = SimpleFSDirectory(File(STORE_DIR))
        searcher = IndexSearcher(directory, True)
        analyzer = SimpleAnalyzer(Version.LUCENE_CURRENT)
        a,b,c,d,e,f,g= func(user_data.keyword,searcher,analyzer)
        searcher.close()
        return render.result(form1,a,b,c,d,e,f,g)

if __name__ == "__main__":
    while True:
        app = web.application(urls, globals())
        app.run()
