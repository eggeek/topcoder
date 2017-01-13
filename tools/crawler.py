#!/usr/bin/env python
# -*-: encoding: utf-8 -*-
import requests
import HTMLParser
import re
from pyquery import PyQuery as pq
from tinydb import TinyDB, Query

h = HTMLParser.HTMLParser()
ignore = ["README.md", "clear.py", "cpp.tmpl", "greed.conf", "py.tmpl", "tools"]


def crawl_round(rid, round_name):
    url = "https://community.topcoder.com/stat?c=round_overview&rd=%s" % rid
    print 'requesting seed: %s' % url
    problems = []
    r = requests.get(url)
    html = h.unescape(r.content.decode('utf-8'))
    doc = pq(html)
    div1 = doc('table.alignTop').eq(3)
    level = {"level one": 1, "level two": 2, "level three": 3}
    for tr in div1.children()[2:5]:
        i = pq(tr)
        problem = {}
        problem['rid'] = rid
        problem['round'] = round_name
        problem['level'] = level[i('td').eq(0).text().lower()]
        prob_url = i('td').eq(1).find('a').attr.href
        problem['pid'] = re.findall('pm\=\d+', prob_url)[0].strip('pm=')
        problem['name'] = i('td').eq(1).find('a').text()
        problem['submissions'] = int(i('td').eq(2).text())
        problem['correct_rate'] = float(i('td').eq(3).text().strip('%')) / 100.0
        problem['average_pts'] = float(i('td').eq(4).text())
        problem['solved'] = False
        problems.append(problem)
    return problems


def crawl(sr=0, er=3):
    archive = dict()
    url = "https://community.topcoder.com/tc?module=ProblemArchive&sr=%d&er=%d" % (sr, er)
    print "requesting seed page..."
    r = requests.get(url)
    html = h.unescape(r.content.decode('utf-8'))
    doc = pq(html)
    for i in doc('table.paddingTable2').eq(2).children()[3:]:
        round_name = pq(i).children().eq(2).find('a').text()
        sub_url = pq(i).children().eq(2).find('a').attr.href
        if sub_url is not None:
            rid = sub_url.split('rd=')[-1]
            archive[round_name] = {'rid': rid, 'round': round_name}
    db = TinyDB("db.json")
    tot = len(archive.values())
    cur = 0
    prob_cnt = 0
    for k in archive.values():
        problems = crawl_round(k['rid'], k['round'])
        print 'parse result:'
        for p in problems:
            for pk, pv in p.items():
                print "%-15s:   %s" % (pk, pv)
            prob_cnt += 1
            q = Query()
            if not db.search(q.name == p['name']):
                print '>>>>>>> insert problem: %s' % p['name']
                db.insert(p)
            print '-' * 10
        cur += 1
        print '*' * 10, 'finish', k['round'], ',tot rounds:', tot, 'cur round:', cur, 'round problems:', len(problems), '*' * 10
    print 'done, total round: %d, total problems: %d' % (cur, prob_cnt)

if __name__ == "__main__":
    crawl()
