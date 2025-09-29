#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

void shuffle(char** array, int n){
    for (int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    char* words[] = {
        "et", "in", "est", "non", "qui", "cum", "ad", "ut", "per", "sed",
        "ex", "sum", "ab", "pro", "a", "sine", "si", "quam", "aut", "ne",
        "ego", "ille", "hic", "is", "quod", "quae", "ideo", "quia", "quoniam",
        "enim", "nam", "quidem", "tamen", "at", "autem", "igitur", "ergo", "etiam",
        "nunc", "iam", "dum", "ubi", "unde", "donec", "nisi", "nec", "an", "quis",
        "aliquis", "alius", "quisque", "ipse", "idem", "iste", "quicumque", "quasi",
        "usque", "num", "vel", "quoque", "quanquam", "utrum", "scilicet", "quin",
        "cui", "eo", "eum", "eius", "eam", "eis", "eidem", "ei", "ipsum", "ipsa",
        "eodem", "hunc", "huius", "hoc", "his", "haec", "hujus", "huic", "illum",
        "illius", "illi", "illos", "illas", "illa", "illud", "illorum", "eadem",
        "easdem", "earum", "eorum", "eisdem", "nemo", "nihil", "aliquid", "quidam",
        "quid", "cuius", "quem", "quo", "quibus", "homo", "res", "dies", "manus",
        "domus", "nox", "lex", "mors", "pars", "vox", "urbs", "tempus", "verbum",
        "corpus", "opus", "nomen", "genus", "caput", "flumen", "iter", "animal",
        "mare", "os", "consilium", "auxilium", "bellum", "arma", "castra", "imperium",
        "regnum", "consul", "rex", "senatus", "civitas", "populus", "militia",
        "hostis", "duces", "virtus", "gloria", "amor", "vita", "fortuna", "dea",
        "fama", "terra", "aqua", "caelum", "luna", "sol", "lux", "tempestas",
        "hora", "via", "porta", "ager", "campus", "mons", "silva", "rivus", "puer",
        "vir", "filius", "frater", "mater", "pater", "uxor", "dominus", "servus",
        "amicus", "liber", "magister", "discipulus", "imperator", "miles", "gladius",
        "sagitta", "navis", "equus", "pontus", "insula", "templum", "forum", "murus",
        "turis", "annus", "ver", "hiems", "aestas", "autumnus", "pes", "oculus",
        "auris", "lingua", "nasus", "venter", "pectus", "digitus", "sanguis",
        "cerebrum", "mens", "spiritus", "odum", "timor", "ira", "gaudium", "dolor",
        "cura", "labor", "honor", "fides", "pax", "iudicium", "poena", "filia",
        "soror", "maritus", "libertus", "femina", "puella", "senex", "infans",
        "inimicus", "regina", "tribunus", "praetor", "censor", "dictator", "doctus",
        "stultus", "fortis", "audax", "timidus", "pulcher", "laetus", "tristis",
        "magnus", "parvus", "bonus", "malus", "novus", "vetus", "longus", "brevis",
        "altus", "humilis", "clarus", "obscurus", "celer", "tardus", "ferus",
        "domesticus", "gratus", "ingratus", "difficilis", "facilis", "similis",
        "dissimilis", "iustus", "iniustus", "sanus", "aeger", "dives", "pauper",
        "verus", "falsus", "certus", "incertus", "totus", "nullus", "unus", "duo",
        "tres", "quattuor", "quinque", "sex", "septem", "octo", "novem", "decem",
        "centum", "mille", "primus", "secundus", "tertius", "quartus", "quintus",
        "sextus", "septimus", "octavus", "nonus", "decimus", "ante", "post",
        "inter", "prope", "infra", "supra", "sub", "de", "contra", "ob", "trans",
        "ultra", "circa", "iuxta", "praeter", "secundum", "versus", "extra", "ita",
        "sic", "certe", "modo", "semper", "numquam", "tum", "tunc", "deinde",
        "postea", "primum", "iterum", "mox", "statim", "hodie", "heri", "cras",
        "nondum", "paulisper", "diu", "olim", "semel", "bis", "ter", "quater",
        "saepe", "raro", "subito", "tandem", "forte", "casu", "vero", "plane",
        "vix", "parum", "nimis", "satis", "multum", "plus", "minus", "tanto",
        "totiens", "quoties", "tam", "quando", "postquam", "antequam", "neque",
        "ac", "atque", "itaque"
    };

    int word_count = sizeof(words) / sizeof(words[0]);

    FILE *fp = fopen("latin.bin", "wb");
    if (!fp) {
        perror("Error creating latin.bin");
        return 1;
    }

    srand(time(NULL));

    shuffle(words, word_count);

    for (int i = 0; i < word_count; i++) {
        uint8_t len = (uint8_t)strlen(words[i]);
        fwrite(&len, sizeof(uint8_t), 1, fp);
        fwrite(words[i], sizeof(char), len, fp);
    }

    fclose(fp);
    printf("'latin.bin' file successfully generated (%d words).\n", word_count);
    return 0;
}