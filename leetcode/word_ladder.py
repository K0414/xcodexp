from nose.tools import assert_equal

class Solution:
    # @param start, a string
    # @param end, a string
    # @param dict, a set of string
    # @return an integer
    def ladderLength(self, start, end, dict):
        return self._solve_bfs2(start, end, dict)
        n = self._solve(start, end, dict, 1, len(dict)+2)
        if n >= len(dict)+2:
            return 0
        else:
            return n

    def _solve(self, start, end, dict, step, minTrans):
        print step, start, end, dict
        if step >= minTrans:
            return minTrans

        if self._diff(start, end) == 1:
            return step+1

        if len(dict) == 0:
            return 0

        m = minTrans
        for w in dict:
            if self._diff(w, start) == 1:
                dict.remove(w)
                ret = self._solve(w, end, dict, step+1, m)
                if ret > 0 and ret < m:
                    m = ret
                dict.add(w)
        return m

    def _diff(self, w1, w2):
        diff = 0
        for l1, l2 in zip(w1, w2):
            if l1 != l2:
                diff += 1
                if diff > 1:
                    return 2
        return diff

    def _solve_bfs(self, start, end, dict):
        q1 = [ start ]
        q2 = list()
        step = 1
        visited = []
        while q1:
            #print q1
            for w in q1:
                if self._diff(w, end) == 1:
                    return step + 1
                for item in dict:
                    if item in q2:
                        continue
                    if self._diff(item, w) == 1:
                        q2.append(item)
                        visited.append(item)
                for x in visited:
                    dict.remove(x)
                visited = []
            q1, q2 = q2, []
            step += 1
        return 0

    def _solve_bfs2(self, start, end, dict):
        q1 = [ start ]
        q2 = list()
        alphabet = [chr(c) for c in range(ord('a'), ord('z')+1)]
        step = 1
        while q1:
            #print q1
            for w in q1:
                for i in range(len(w)):
                    l = list(w)
                    tmp = l[i]
                    for char in alphabet:
                        if tmp == char:
                            continue
                        l[i] = char
                        new = ''.join(l)
                        if (new == end):
                            return step + 1
                        if (new in dict):
                            q2.append(new)
                            dict.remove(new)
            q1, q2 = q2, []
            step += 1
        return 0


class TestSolution(object):

    def test_simple(self):
        s = Solution()

    def test_example(self):
        s = Solution()
        start = "hit"
        end = "cog"
        dict = set(["hot","dot","dog","lot","log"])
        assert_equal(s.ladderLength(start, end, dict), 5)
        start = 'qa'
        end = 'sq'
        dict = set(["si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"])
        assert_equal(s.ladderLength(start, end, dict), 5)
        start = "nape"
        end = "mild"
        dict = set(["dose","ends","dine","jars","prow","soap","guns","hops","cray","hove","ella","hour","lens","jive","wiry","earl","mara","part","flue","putt","rory","bull","york","ruts","lily","vamp","bask","peer","boat","dens","lyre","jets","wide","rile","boos","down","path","onyx","mows","toke","soto","dork","nape","mans","loin","jots","male","sits","minn","sale","pets","hugo","woke","suds","rugs","vole","warp","mite","pews","lips","pals","nigh","sulk","vice","clod","iowa","gibe","shad","carl","huns","coot","sera","mils","rose","orly","ford","void","time","eloy","risk","veep","reps","dolt","hens","tray","melt","rung","rich","saga","lust","yews","rode","many","cods","rape","last","tile","nosy","take","nope","toni","bank","jock","jody","diss","nips","bake","lima","wore","kins","cult","hart","wuss","tale","sing","lake","bogy","wigs","kari","magi","bass","pent","tost","fops","bags","duns","will","tart","drug","gale","mold","disk","spay","hows","naps","puss","gina","kara","zorn","boll","cams","boas","rave","sets","lego","hays","judy","chap","live","bahs","ohio","nibs","cuts","pups","data","kate","rump","hews","mary","stow","fang","bolt","rues","mesh","mice","rise","rant","dune","jell","laws","jove","bode","sung","nils","vila","mode","hued","cell","fies","swat","wags","nate","wist","honk","goth","told","oise","wail","tels","sore","hunk","mate","luke","tore","bond","bast","vows","ripe","fond","benz","firs","zeds","wary","baas","wins","pair","tags","cost","woes","buns","lend","bops","code","eddy","siva","oops","toed","bale","hutu","jolt","rife","darn","tape","bold","cope","cake","wisp","vats","wave","hems","bill","cord","pert","type","kroc","ucla","albs","yoko","silt","pock","drub","puny","fads","mull","pray","mole","talc","east","slay","jamb","mill","dung","jack","lynx","nome","leos","lade","sana","tike","cali","toge","pled","mile","mass","leon","sloe","lube","kans","cory","burs","race","toss","mild","tops","maze","city","sadr","bays","poet","volt","laze","gold","zuni","shea","gags","fist","ping","pope","cora","yaks","cosy","foci","plan","colo","hume","yowl","craw","pied","toga","lobs","love","lode","duds","bled","juts","gabs","fink","rock","pant","wipe","pele","suez","nina","ring","okra","warm","lyle","gape","bead","lead","jane","oink","ware","zibo","inns","mope","hang","made","fobs","gamy","fort","peak","gill","dino","dina","tier"])
        assert_equal(s.ladderLength(start, end, dict), 6)
