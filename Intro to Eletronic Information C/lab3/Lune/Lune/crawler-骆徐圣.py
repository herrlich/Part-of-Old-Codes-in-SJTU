# -*- coding:gbk -*-
from BeautifulSoup import BeautifulSoup
import urllib2
import re
import urlparse
import os
import urllib
import threading
import Queue
import time
import sys

def valid_filename(s):
    import string
    valid_chars = "-_.() %s%s" % (string.ascii_letters, string.digits)
    s = ''.join(c for c in s if c in valid_chars)
    return s

def get_page(page):
    content = ''
    #print page
    try:
        content = urllib2.urlopen(page,timeout=1).read()
    except:
        content =''
    return content

def get_all_links(content, page):
    links = []
    soup = BeautifulSoup(content)
    for i in soup.findAll('a',{'href' : re.compile('^http|^/')}):
        links.append(str(urlparse.urljoin(page,i['href'])))

    return links

def add_page_to_folder(page, content): #����ҳ�浽�ļ��������ַ�Ͷ�Ӧ���ļ���д��index.txt��
    index_filename = 'index.txt'    #index.txt��ÿ����'��ַ ��Ӧ���ļ���'
    folder = 'html'                 #�����ҳ���ļ���
    filename = valid_filename(page) #����ַ��ɺϷ����ļ���
    index = open(index_filename, 'a')
    index.write(page.encode('ascii', 'ignore') + '\t' + filename + '\n')
    index.close()
    if not os.path.exists(folder):  #����ļ��в��������½�
        os.mkdir(folder)
    f = open(os.path.join(folder, filename), 'w')
    f.write(content)                #����ҳ�����ļ�
    f.close()

def working():
    global count
    while True:
        page = q.get()
        if page not in crawled:
            if (count < 1000):
                content = get_page(page)
                count = count + 1
            else:
                content = ""
            add_page_to_folder(page, content)
            print page
            outlinks = get_all_links(content, page)
            for link in outlinks:
                q.put(link)
            if varLock.acquire():
                crawled.append(page)
                graph[page] = []
                for i in outlinks:
                    graph[page].append(i)
                varLock.release()
        q.task_done()
    return graph


start = time.clock()
NUM = 100
count = 0
crawled = []
graph={}
varLock = threading.Lock()
q = Queue.Queue()
q.put('http://www.sjtu.edu.cn')
for i in range(NUM):
    t = threading.Thread(target=working)
    t.setDaemon(True)
    t.start()
q.join()
end = time.clock()
print end-start

