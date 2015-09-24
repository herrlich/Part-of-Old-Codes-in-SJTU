def bbs_set(id, pw, text):
    import urllib2, cookielib, urllib
    from BeautifulSoup import BeautifulSoup
    cj=cookielib.CookieJar()
    opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    urllib2.install_opener(opener)
    postdata=urllib.urlencode({'id':id,'pw':pw,'submit':'login'})
    req=urllib2.Request(url='https://bbs.sjtu.edu.cn/bbslogin',data=postdata)
    content=urllib2.urlopen(req)
    content=urllib2.urlopen('https://bbs.sjtu.edu.cn/bbsplan').read()
    t=text.encode('gbk')
    newdata=urllib.urlencode({'text':t,'type':'update'})
    newreq=urllib2.Request(url='https://bbs.sjtu.edu.cn/bbsplan',data=newdata)
    newcontent=urllib2.urlopen(newreq)
    content=urllib2.urlopen('https://bbs.sjtu.edu.cn/bbsplan').read()
    soup=BeautifulSoup(content)
    print str(soup.find('textarea').string).strip().decode('utf8')

#这个程序在运行时必须注意加入下面三行代码：
import sys
reload(sys)
sys.setdefaultencoding('utf8')