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
def renren_set(email, password,text):
    import urllib2, cookielib, urllib
    from BeautifulSoup import BeautifulSoup
    cj=cookielib.CookieJar()
    opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    urllib2.install_opener(opener)
    postdata=urllib.urlencode({'email':email,'password':password,'captcha_type':'web_login','icode':'','origURL':'http://www.renren.com/indexcon','domain':'renren.com','key_id':'1'})
    req=urllib2.Request(url='http://www.renren.com/PLogin.do',data=postdata)
    response = urllib2.urlopen(req)
    content=response.read()
    j=content[content.find('script'):]
    rtk=j[j.find('get_check_x:') +13:j.find('get_check_x:')+21]
    newdata=urllib.urlencode({'_rtk':rtk,'channel':'renren','content':text,'hostid':'468754132'})
    newreq=urllib2.Request(url='http://shell.renren.com/468754132/status',data=newdata)
    newcontent=urllib2.urlopen(newreq)
    newpostdata = urllib.urlencode({'id':'729595072','portal':'homeFootprint','ref':'home_footprint'})
    newurl = 'http://www.renren.com/profile.do?portal=homeFootprint&ref=home_footprint&id=729595072?%s' % newpostdata
    newresponse = urllib2.urlopen(newurl)