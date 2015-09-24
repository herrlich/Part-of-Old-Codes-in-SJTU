def get_page(page):
    return g.get(page, [])

def get_all_links(content):
    return content

def union_dfs(a,b):
    for e in b:
        if e not in a:
            a.append(e)

def union_bfs(a,b):
    for i in b:
        if i not in a:
            a.insert(0,i)

def crawl(seed, method):
    tocrawl = [seed]
    crawled = []
    graph = {}
    while tocrawl:
        page = tocrawl.pop()
        if page not in crawled:
            content = get_page(page)
            outlinks = get_all_links(content)
            graph[page]=outlinks
            globals()['union_%s' % method](tocrawl, outlinks)
            if method=='dfs':
                crawled.append(page)
            if method=='bfs':
                crawled.insert(0,page)
    if method=='bfs':
        crawled.reverse()
    return graph, crawled

g = {'A':['B', 'C', 'D'],\
     'B':['E', 'F'],\
     'D':['G', 'H'],\
     'E':['I', 'J'],\
     'G':['K', 'L']}

graph_dfs, crawled_dfs = crawl('A', 'dfs')