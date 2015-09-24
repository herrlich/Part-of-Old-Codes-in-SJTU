def parseQiushibaikePic(content):
    import sys
    reload(sys)
    sys.setdefaultencoding('utf8')
    import re
    from BeautifulSoup import BeautifulSoup
    soup=BeautifulSoup(content)
    docs={}
    nextpage=''
    temp=soup.find('div',{'class':'col1'})
    for i in temp.findAll('div',{'class':'block untagged'}):
        docs[i['id']]={}
        for j in i.findAll('div',{'class':'content'}):
            docs[i['id']]['content']=str(j.string).encode('utf8')
        for k in i.findAll('div',{'class':'thumb'}):
            docs[i['id']]['imgurl']=k.find('img')['src']
    for i in soup.findAll('a',{'class':'next'}):
        nextpage='http://www.qiushibaike.com'+i['href']
    return docs,nextpage