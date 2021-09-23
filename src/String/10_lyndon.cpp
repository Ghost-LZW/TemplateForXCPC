std::vector<std::string> lyndon(string s, int n) {
	std::vector<std::string> v;
	for (int i = 0; i < n;) {
        int j = i, k = i + 1;

        while (k < n and s[j] <= s[k]) {
            if (s[j] < s[k])
                j = i;
            else ++j;
            ++k;
        }

        while (i <= j) {
        	v.emplace_back(s.substr(i, k - j));
            i += k - j;
        }
    }
    return v;
}