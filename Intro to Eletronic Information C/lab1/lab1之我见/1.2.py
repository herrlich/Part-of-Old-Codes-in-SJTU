def parseIMG(content):
    import re
    from BeautifulSoup import BeautifulSoup
    soup=BeautifulSoup(content)
    imgset = set()
    for i in soup.findAll('img',{'src':re.compile('^http*')}):
        imgset.add(i['src'])
    return imgset
