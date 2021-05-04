#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>

#include <gtest/gtest.h>

#include "trie.h"

using trie = node_t<int>;

TEST (TRIE, Empty)
{
    trie root;
    EXPECT_FALSE(find(&root, "A string"));
}

TEST(TRIE, Insert)
{
    trie root;
    EXPECT_FALSE(find(&root, "A"));
    insert(&root, "A", 12345);
    EXPECT_TRUE(find(&root, "A"));
    EXPECT_EQ(find(&root, "A").value(), 12345);
    EXPECT_FALSE(find(&root, "B"));
    EXPECT_FALSE(find(&root, "AB"));
}

TEST(TRIE, Insert2)
{
    trie root;
    insert(&root, "A", 12345);
    insert(&root, "AB", 23456);
    EXPECT_TRUE(find(&root, "A"));
    EXPECT_EQ(find(&root, "A").value(), 12345);
    EXPECT_TRUE(find(&root, "AB"));
    EXPECT_EQ(find(&root, "AB").value(), 23456);
    EXPECT_FALSE(find(&root, "B"));
}

TEST(TRIE, words)
{
    if(std::filesystem::exists("/usr/share/dict/words"))
    {
        trie root;
        std::ifstream ist("/usr/share/dict/words");
        std::string wd;
        trie::val_type x { 0 };
        auto s1 = std::chrono::steady_clock::now();
        while(std::getline(ist, wd))
        {
            insert(&root, wd, x);
            ++x;
        }
        auto e1 = std::chrono::steady_clock::now();
        std::cout << "Read and inserted " << x << " words in " << std::chrono::duration_cast<std::chrono::microseconds>(e1 - s1).count()  << " us.\n";
 
        EXPECT_TRUE(find(&root, "elephant"));
        EXPECT_FALSE(find(&root, "elephont"));
        EXPECT_TRUE(find(&root, "Zygosaccharomyces"));
        EXPECT_EQ(find(&root, "Zygosaccharomyces").value(), 235815);

        constexpr std::string_view test_words[]{"abdal", "abilla", "aboma", "abscissa", "abstrusely", "acanthial", "accensor", "accompanyist", "acediast", "acetone", "achievement",
        "acidimetric", "acolous", "acreman", "acromphalus", "Actinobacillus", "actualistic", "Adansonia", "Adeleidae", "adeptness", "adjectival", "admonisher", "adrenine", "adventive",
        "aegagrus", "Aerocharidae", "aerotherapeutics", "affinitative", "African", "afterplanting", "Agapemone", "aggrandizement", "agnatically", "agriologist", "ahull", "airmonger",
        "akmuddar", "Alauda", "albuminometry", "aldane", "alethopteis", "algidity", "alimentative", "alkoxide", "allgood", "allophylian", "almadia", "alopecia", "alterant", "aluminum", 
        "Amanist", "ambicolorate", "ambulator", "ametropic", "aminolysis", "amnestic", "Ampelis", "amphimacer", "amplidyne", "amylidene", "anachronismatical", "Anahita", "Ananite",
        "anastasimos", "anchorhold", "androcyte", "anemotropism", "angiectasis", "anglewing", "anhematosis", "animotheism", "ankus", "annoyingly", "anomurous", "answer", "antefurcal",
        "anteroventrally", "Anthospermum", "anthropometrical", "antianthropocentric", "anticlerical", "antidynamic", "antiheroic", "antimetrical", "antiparliamentarist", "antipriming",
        "antiscorbutical", "antithenar", "antonymy", "apachite", "Aphelops", "apicultural", "apocryph", "apophasis", "apotheose", "appet", "appreciatorily", "apteral", "Arab", "Araquaju",
        "Arceuthobium", "Archegoniata", "archimperial", "archprelatic", "ardennite", "argentamin", "Arianistical", "Arkansawyer", "Aroides", "arrogatingly", "Artemis", "arthroneuralgia",
        "Aruac", "ascertainableness", "asexualize", "asonant", "aspish", "asseveratingly", "assumptious", "astigmatoscope", "astrometrical", "atavi", "athetosic", "atokous", "atrorubent",
        "attorneyism", "audivision", "Aureocasidium", "Aussie", "autoanalytic", "autoeducation", "automaton", "autoscopic", "auxiliate", "averter", "awake", "axiolitic", "azimuth", "B", 
        "bacao", "backfiring", "Bacopa", "badland", "baikerite", "balagan", "Balinese", "balneologist", "banco", "bankerdom", "Barbara", "baresark", "barolo", "barsom", "basibregmatic",
        "Basoga", "bathochromatic", "batterfang", "baywood", "bearbaiter", "beballed", "becrimson", "bedrabble", "beermaking", "begartered", "behavioristically", "beleap", "bellwaver", 
        "bemolt", "benighted", "benzo", "bepommel", "Bern", "beseemly", "besplatter", "Bethesda", "bevesseled", "Bhima", "bibliophagist", "bicuspid", "bigbloom", "bilimbing", "bimastism",
        "bioclimatology", "biostatical", "birdbander", "biseptate", "biternately", "bizygomatic", "blae", "blastodermic", "Blechnum", "blessedness", "blockheadism", "blotter", "bluing",
        "boatside", "Boehmenite", "bolection", "Bombus", "bony", "boonless", "Boreiad", "bosom", "bottleflower", "bourgeoisitic", "boxhaul", "brachycephalous", "bradypeptic", "brakemaker",
        "brasiletto", "breadroot", "breezy", "brickmason", "brightwork", "broadish", "bromidic", "bronchostenosis", "Broussonetia", "brushman", "buccula", "budlet", "bulbule", "bullydom",
        "bunker", "burgomaster", "burton", "butchery", "butyrometer", "C", "cachinnate", "cadalene", "Caesarist", "cakewalk", "calciform", "calicle", "calm", "calycoid", "camera", "cample",
        "cancerophobe", "canid", "Canossa", "capacitative", "capocchia", "captainess", "carbamate", "carburetant", "cardiodysneuria", "Carettochelydidae", "carminite", "carpetbeater",
        "cart", "casave", "Cassie", "caswellite", "cataphoretic", "categorematic", "catholicate", "caudices", "cautiously", "Cecil", "celiohysterotomy", "cementitious", "centillionth", 
        "cepe", "ceral", "cerebellar", "cerolite", "cessionary", "Chaetophorales", "chalcograph", "chambray", "chankings", "characterization", "charterable", "chauk", "cheep", "chelp",
        "Chermish", "chicaric", "Chilean", "chinchilla", "Chironomidae", "chloralism", "chlorophylligerous", "cholecystic", "chondriome", "choralist", "choruslike", "chromaphore",
        "chromophilic", "chrysaloid", "chuhra", "chylocaulous", "cigarillo", "cinephotomicrography", "circulatory", "circumrotation", "cisted", "civism", "clangful", "classis", "clayer",
        "cleoid", "climatological", "clitellar", "clonicotonic", "cloyedness", "cnicin", "coaita", "coaxer", "coccobacillus", "cocklewife", "codiaceous", "coembedded", "coexpire",
        "cogovernor", "cointerest", "Coliiformes", "collery", "collyrium", "colorlessly", "columniferous", "comendite", "commendingly", "commonplacely", "comparatively", "complanation",
        "compoundedness", "conationalistic", "Conchifera", "concubinate", "conductility", "confessorship", "confronter", "congruently", "connach", "consanguinity", "consignificative", 
        "constitute", "contactor", "Continentaler", "contradistinct", "controller", "conversationally", "cooer", "copemate", "coprophilism", "Corallinaceae", "Corema", "cornerways", 
        "coroparelcysis", "corrige", "corundum", "cosmetological", "costmary", "cottagers", "counselful", "counterdiscipline", "countermovement", "countersecure", "countrypeople",
        "covenantal", "cowwheat", "cradlemaker", "craniopuncture", "cravenness", "credensive", "creophagist", "cribrose", "crippledom", "crofter", "crosslight", "crownwork", "crush",
        "cryptodiran", "crystalloluminescence", "cuckhold", "culminant", "cumshaw", "cuprum", "curmudgeon", "curvinerved", "cutlips", "cyanuramide", "cyclonoscope", "cylindroogival",
        "Cynopithecidae", "cysticercoidal", "cytogene", "dachshound", "Daemonelix", "daleth", "Danaid", "Daphnean", "dartre", "daughterliness", "deacidification", "deash", "debtorship", 
        "decarnated", "dechlore", "declivitous", "decretal", "deepener", "deferrable", "deformeter", "dehortatory", "Delaware", "deliriant", "demeanor", "demioctagonal", "demoniac",
        "Dendrites", "densher", "deobstruent", "depilate", "depriorize", "dermamyiasis", "dermophytic", "desertful", "desmocytoma", "desquamate", "deteriorative", "deuterogelatose", 
        "devilwise", "dexterousness", "diabrosis", "dialecticism", "Diapensiaceae", "diathermous", "Dicentra", "dictatorialism", "Didynamia", "diffusibly", "digressive", "diligently",
        "dimorphism", "dioecian", "diphtheritically", "diplopy", "directrix", "disappear", "discerning", "discomposed", "discoverably", "disembogue", "disgorgement", "disimitation",
        "disluster", "dispauper", "disposition", "disrespectfulness", "dissipater", "distinctional", "disuniter", "divellicate", "divulgement", "doctrinal", "dogeless", "dolichocephalize",
        "dominance", "dooli", "dorsale", "dothienenteritis", "doveling", "downtrampling", "dragman", "drawbench", "drenchingly", "Drokpa", "drugger", "duarchy", "dufferdom", "dumpling",
        "duotype", "dustman", "dynamogenous", "dysphasia", "earthgall", "ebriously", "Echinoderma", "ecphore", "ectrodactylia", "editor", "effendi", "egocentrism", "ejection", "elaterid", 
        "electrocardiogram", "electrometallurgical", "electrotonic", "elevener", "elod", "emanate", "embody", "embryotome", "emotionalism", "empyreal", "encaenia", "encinillo", "endable",
        "endocrinism", "endopterygotic", "Endymion", "enginous", "enhypostatize", "ennoic", "ensignship", "enterocoelic", "entire", "entozoological", "enwoman", "epencephalon", "epicedium",
        "epidictic", "epimandibular", "episcopacy", "epithalamus", "epsilon", "equilobed", "eradiate", "ergophobiac", "erotetic", "Erythraeidae", "eschara", "esotericist", "esteemable", 
        "ethaldehyde", "ethnogeny", "eucalyptol", "euglenoid", "euphemy", "eurypterid", "evangelicality", "evertebral", "exactness", "excellent", "excogitate", "executiveship", "exhilarate",
        "exogastritis", "exotropic", "experimenter", "exposition", "exsomatic", "extirpator", "extramurally", "extraversion", "eyelid", "faciation", "fagaceous", "falcated", "familiarness",
        "faradic", "fasciated", "fatherlike", "favn", "featural", "feignedness", "feminate", "Feringi", "ferrous", "fetterless", "fibrinose", "fictionistic", "fife", "filially", "fimbriation",
        "finishing", "firm", "Fissipedia", "fizzer", "flamboyantize", "flattener", "flectional", "flightiness", "floccus", "florikan", "fluently", "fluoroscope", "flytier", "folding", "foo",
        "foppishness", "foreassurance", "forego", "foreplace", "forestful", "forgettingly", "Formicinae", "fortification", "foujdary", "foxproof", "francolin", "fraze", "frenched", "fridstool",
        "fritt", "frontomaxillary", "fruitarianism", "fugler", "fume", "funiculitis", "furrier", "futural", "gaff", "Galago", "gallery", "galvanical", "gametogonium", "ganglioneuron", "gardenlike",
        "gas", "gastroarthritis", "gastrorrhaphy", "gauntleted", "Geat", "gelidly", "generalia", "genitourinary", "geobotanist", "geomorphology", "Gerasene", "gerontocratic", "gez", "giber", "Gilia",
        "giornatate", "glaciered", "glass", "glenoidal", "glochidial", "glossolysis", "glumal", "glycolytically", "gnetaceous", "goblinesque", "gold", "gonapophysis", "gonytheca", "gorgedly",
        "Gothonic", "graciosity", "graminiform", "granitiform", "graphoscope", "gravelish", "greedygut", "greige", "grinder", "groined", "groupment", "grumphy", "guardedly", "guesthouse", "gular",
        "gunnery", "guttable", "Gymnodontes", "gynomonoecism", "Habab", "Hadentomoidea", "hagiolater", "halberd", "hallucinatory", "Hamiticized", "handkerchief", "haoma", "hardhandedness", "harmonograph",
        "hasky", "haulback", "hayfork", "headspring", "heartsette", "Hebraean", "hedyphane", "Helianthoidean", "heliotropism", "Helot", "hematocytometer", "hemiasynergia", "hemiolic", "hemodilution",
        "henbane", "hepatoperitonitis", "Heraclitic", "Hereford", "Herniaria", "Hesperid", "heterodontism", "Heteroneura", "heterotropic", "hexametric", "hibernaculum", "hierologist", "hilum",
        "hippocentauric", "Hirtella", "historied", "hobbling", "holard", "hologamy", "Homalopterous", "homiletic", "homogametic", "homopterous", "honorableness", "hooven", "horner", "horselaugh",
        "hotchpot", "houseroom", "huckstery", "humanness", "humpbacked", "hurroo", "hyaenodont", "hydrargyrosis", "hydrocobalticyanic", "hydromechanics", "hydropropulsion", "hyenoid", "hymeneals",
        "hyperabsorption", "hyperdemocratic", "hypermakroskelic", "hyperprognathous", "hypethral", "hypochondriac", "hypoionian", "hyporhachis", "hypovalve", "hysterolaparotomy", "icacinaceous",
        "ichthyophobia", "idalia", "idiopathical", "idyllically", "iliahi", "illocal", "imaginariness", "immanental", "immodest", "imparidigitate", "impenitent", "impersuasibleness", "imploring",
        "impracticality", "improvidence", "inadaptive", "inarticulately", "Incarvillea", "inclose", "incomposedly", "incontaminate", "increscence", "indecent", "indescript", "indignance", "individuate",
        "induplicative", "inequiaxial", "inexpedient", "infectiously", "infit", "infract", "infusionist", "inhabitiveness", "injudicious", "innocuous", "inorganically", "insatisfactorily", "insignificance",
        "inspiritment", "insubordinate", "integrable", "intentive", "interceptress", "intercrescence", "interfluent", "interlamination", "intermessage", "interosculant", "interpupillary", "intersonant",
        "interureteric", "intolerability", "intraleukocytic", "intrathecal", "introversion", "invariable", "invigoratingly", "io", "Iraq", "irisroot", "irrecoverableness", "irrepressibility", "irritomotile",
        "ishshakku", "isocephaly", "isogonal", "isophene", "isotrope", "Iteaceae", "jabbing", "jaculiferous", "jangada", "Jarmo", "Jeanie", "jerib", "Jezebel", "jitney", "Johnsoniana", "josie", "jubilee",
        "Jules", "junto", "juvenilely", "kakarali", "kaneh", "karyomitoic", "katydid", "kelep", "keratoconus", "ketogen", "Khazarian", "kilbrickenite", "kinesiatric", "kippeen", "kiver", "kneepan",
        "knotwort", "kokil", "korec", "Krishnaist", "kuphar", "labialism", "laccase", "Lacosomatidae", "laden", "laic", "Lamellaria", "lamplighter", "landmil", "Lantana", "lapsability", "larvae", "latah",
        "Latinistic", "laundryowner", "lawyer", "leafery", "leaverwood", "leery", "leguleious", "Lenaeus", "leopardwood", "leptocephalia", "Lestrigon", "leucoderma", "Leviticism", "liberationism", "lictor",
        "lightener", "lile", "limmock", "line", "linkman", "lipocyte", "lisere", "lithochromatographic", "litigation", "Liz", "lobsterproof", "loculicidally", "logogogue", "Londonize", "looping", "lori",
        "loutrophoros", "loyalty", "luctiferousness", "lumbocolostomy", "lunular", "lutanist", "lycoperdon", "lymphosarcomatosis", "macaasim", "macle", "macromethod", "madarosis", "magazinage", "magnetogenerator",
        "Mahri", "majo", "malanga", "malformation", "malonylurea", "mammonite", "mandola", "Manichaeanize", "Manny", "manufactural", "Marattiaceae", "margin", "marksmanly", "marshalcy", "Marxist", "massiest",
        "mastoplastia", "matildite", "matutinal", "Maybird", "mealiness", "Mechitaristican", "medicolegal", "meekly", "megalosaurian", "melaconite", "melch", "mellowly", "membranocartilaginous", "meningococcemia",
        "menthane", "mercurial", "meroceritic", "mescalism", "mesocoracoid", "Mesosauria", "metabatic", "metalism", "metaphenylene", "metatantalic", "methanoic", "metrectomy", "Mezentism", "microbial", "microdont",
        "micromethod", "microscopic", "micturition", "mighty", "milklike", "millionist", "mimsey", "minimum", "Miocenic", "misanthropically", "mischoose", "misdower", "misidentification", "misogynist", "misreposed",
        "mistletoe", "mitrailleuse", "Mobilian", "Modoc", "moksha", "mollyhawk", "monandry", "Mongolic", "monocarbonate", "monodist", "monomerous", "monopolylogist", "monotic", "Montezuma", "moonsickness",
        "Moravian", "Mormonism", "morrowless", "Mosquito", "motored", "mousery", "muciferous", "mudland", "mulishly", "multifoliolate", "multipotent", "mummydom", "murga", "muscovado", "muskflower", "mutilous",
        "mycologically", "myelospongium", "myonosus", "Myriophyllum", "mystes", "Myxogastres", "naething", "namaz", "naphthoxide", "narrow", "nataloin", "nauplioid", "Neapolitan", "necrographer", "needling",
        "neighboress", "neoclassic", "neoterically", "nephron", "Neslia", "neurectasia", "neuromuscular", "neutral", "Nhan", "nidge", "nignye", "Niobite", "nitromuriatic", "noctilucence", "nomadically", "nonaction",
        "nonarbitrable", "nonburgage", "noncoincidental", "noncongenital", "noncriminal", "nondesecration", "nondrying", "nonerudite", "nonfastidious", "nongospel", "noninfallibilist", "nonlinear", "nonmultiple",
        "nonparasitism", "nonpostponement", "nonputting", "nonrepresentational", "nonsanity", "nonsocialistic", "nonsurgical", "nontropical", "nonvolant", "Normanish", "nosogeny", "nothingology", "novantique",
        "nubility", "nulliparity", "nunni", "Nyctea", "oasitic", "objectivistic", "obreptitiously", "obstructionist", "occipitofrontal", "ochroid", "octocotyloid", "ocypodian", "odontophorous", "oes", "oftentime",
        "okia", "olibanum", "Olividae", "ommateal", "omophagia", "onerously", "onycha", "oorali", "operculiform", "ophthalmometric", "opisthographic", "optably", "orant", "orchiditis", "organical", "orientalist",
        "Ornithodelphia", "Orphically", "orthogonally", "orthoxazin", "Osiridean", "ossuarium", "osteometric", "otalgic", "otopathic", "outbleat", "outdream", "outhue", "outpensioner", "outscream", "outstrike",
        "outword", "overafflict", "overbound", "overcivil", "overcrowded", "overdraft", "overfamed", "overgaze", "overhit", "overlabor", "overmask", "overpast", "overprovidently", "overrunning", "oversimplicity",
        "overstowed", "overthwartness", "overwhipped", "ovovitellin", "oxcheek", "oxydiact", "oysterhood", "pachyhaemia", "Padina", "paideutics", "palaeobotanist", "Palaeotheriidae", "paled", "paleopsychic",
        "pallescence", "palolo", "pamphletwise", "pandanaceous", "panhead", "panosteitis", "pantheon", "papability", "pappescent", "parachromoparous", "paraform", "parallelogrammatical", "paraparesis", "parasitize",
        "parcel", "pargasite", "parlous", "parotitis", "parthenogeny", "parvirostrate", "passivism", "patchable", "patholytic", "patrocliny", "paulospore", "Payaguan", "peasant", "pectoriloquial", "pediatrics",
        "peeler", "pelargonidin", "peltatodigitate", "pendulously", "penninite", "pentagram", "penthiophen", "peptical", "Perciformes", "perfectist", "peribolos", "Peridiniales", "perinephral", "peripheromittor",
        "peristele", "perjuredly", "Peromedusae", "persecutory", "persuasibility", "pervious", "Peterkin", "petrosa", "phacomalacia", "phalansterist", "Pharaoh", "pharyngopneustal", "phenocrystalline",
        "philanthropism", "Philomachus", "phlebenterism", "Phoebe", "phonophile", "phosphorography", "photoelectrotype", "photonephograph", "phototrophy", "Phryganea", "phyllite", "Physalia", "physiophilosophy",
        "phyton", "piaster", "picnickish", "piedfort", "pigheadedly", "pilidium", "pimpernel", "Ping", "pinnoite", "pipistrel", "pisky", "pitiability", "placer", "plait", "planoconical", "plasmophagy", "platinite",
        "platypodous", "pleasance", "plenilunal", "pleurenchyma", "plicated", "Plowrightia", "plumose", "Plutarchically", "pneumectomy", "pocketful", "podophyllum", "pohna", "Polaris", "politicalize", "poltroonery",
        "polychrome", "polyglot", "polymetochia", "polyphagy", "polysaccharide", "polytokous", "pompiloid", "ponton", "populace", "porokeratosis", "porthole", "pospolite", "postcomitial", "postgenial", "postnatal",
        "postsynsacral", "potentially", "pouncer", "praecognitum", "prankish", "preachingly", "preallowance", "prebroadcasting", "prechoose", "precommissure", "preconsolidated", "precyclonic", "predescribe",
        "predirection", "predraw", "prefloration", "prehaunt", "preinflection", "prelanguage", "premedial", "prenative", "preoutline", "prepotent", "prereport", "prescout", "Presley", "presubordinate", "pretendant",
        "prettily", "prewarn", "priestship", "princelet", "Pristodus", "probability", "procellose", "proconsulship", "Procyon", "proexperiment", "progenerate", "projectively", "prolusory", "pronative", "propellent",
        "proportionability", "proreduction", "prosimian", "prosthetist", "Protelytroptera", "protoblastic", "Protomastigida", "protosyntonose", "proved", "proximad", "psalterion", "pseudoarchaism", "pseudoembryo",
        "pseudomantist", "pseudopore", "pseudotribal", "psyche", "psychopannychistic", "pteridophilistic", "Ptilonorhynchinae", "puckle", "puistie", "pulpitish", "punchless", "punti", "purificator", "pursuer",
        "putschism", "pygobranchiate", "pyramid", "pyroantimonic", "pyrophysalite", "pythogenic", "quadricostate", "quadrivoltine", "quant", "quata", "quencher", "Quidae", "quininize", "quintad", "quizzability",
        "rabbity", "racketer", "radiocinematograph", "radulate", "railwaydom", "rambutan", "ranal", "rantock", "rascalism", "rationalistical", "ravensara", "reactionarism", "reallegorize", "reascertain", "rebase",
        "rebrutalize", "reccy", "reciprocally", "recollectedly", "reconform", "recover", "rectoral", "reddsman", "redient", "redressor", "reetle", "reflexivity", "refreshen", "regermination", "regrow", "reim", 
        "reinsane", "rejoicement", "relevancy", "remainder", "remiped", "renascency", "renumerate", "repatent", "replantable", "representability", "reprover", "requite", "resemblable", "resiliency", "resorcin",
        "restart", "resublime", "retaliation", "retill", "retransplant", "retromigration", "revacate", "reversible", "revokingly", "Rhabdocoelida", "rheoplankton", "rhinoscope", "rhodochrosite", "Rhynchota",
        "Richard", "Riemannean", "rimate", "ripal", "rivalrous", "Robenhausian", "rodent", "roller", "rompishly", "rootstock", "rosetted", "rotorcraft", "roundlet", "royalism", "ruche", "ruglike", "runaway",
        "rusk", "ruttishly", "sabina", "sacciform", "sacristan", "safener", "sailmaking", "salesman", "salmonsite", "saltspoon", "sameness", "sandaliform", "sanguinocholeric", "sapiential", "Saratoga",
        "Sardanapalian", "sassywood", "Saturnal", "saussuritization", "saxicoline", "scaldweed", "Scansores", "Scaridae", "scenecraft", "schism", "schlemiel", "schoolward", "scintilloscope", "sclerocauly",
        "scoleciform", "scorbutus", "Scottishly", "scrat", "scribble", "scrofulotuberculous", "scuffler", "scutellum", "seafardinger", "seater", "secretariat", "sedimental", "seggar", "Selaginaceae", "sellate",
        "semiarc", "semicomical", "semidomed", "semigroove", "seminarial", "semipetaloid", "semisavage", "Semiticize", "Senecio", "sensualism", "septal", "Septuagint", "serenissimi", "sermonize", "serpentwood",
        "servitorial", "setout", "sexennium", "shadbelly", "shakiness", "shankpiece", "shavable", "sheepify", "shelterlessness", "shier", "shiplap", "shockproof", "shopworker", "showerless", "shrubbiness", "siamang",
        "sidecheck", "siftage", "significative", "silicomagnesian", "silverily", "simpler", "singeing", "Sinolog", "Siphonostoma", "sister", "sizar", "skene", "skimmity", "skulking", "slanderousness", "slavocrat",
        "sliced", "slipsloppish", "slouchiness", "slurbow", "smellfungus", "smoky", "snails", "sneer", "snobologist", "snubber", "Sobranje", "sodalist", "solaciousness", "soleplate", "solonetz", "somepart",
        "songlessly", "sophisticated", "sorites", "soulful", "Southumbrian", "spaewife", "sparkless", "spatted", "speckled", "speechmaker", "spermatium", "sphaeridial", "sphericle", "spicket", "spindler", "spiraled", 
        "spirographin", "splayfoot", "splinterd", "spondylotherapy", "sporades", "sportula", "Spring", "spurious", "Squamipennes", "squdge", "squirreline", "stageability", "stalactitiform", "standoffishness",
        "starchlike", "stateliness", "stayable", "steelwork", "stema", "stephane", "stereometric", "sternoglossal", "stichometry", "stilly", "stirabout", "stoichiometric", "stonebrood", "storge", "straddlebug",
        "straphanger", "streamhead", "stretcherman", "stringent", "stronghearted", "Struthiomimus", "stummy", "styliferous", "subacademic", "subbailie", "subcommended", "subdemonstration", "subequilateral",
        "subhatchery", "subjectness", "submedian", "subordinary", "subpunch", "subsequently", "substitutionary", "subtonic", "subvirile", "suckener", "suffragan", "Sukey", "sulfurate", "sulphochloride", "sulphury",
        "sumptuously", "sunstone", "superazotation", "superdeclamatory", "superextend", "superimprobable", "supermishap", "superpowered", "supersistent", "supervenience", "supposititious", "supraoptional",
        "surfacy", "surrogation", "sustainingly", "swale", "swayable", "swerve", "Swithin", "syllabation", "Symbranchia", "symposia", "synchondrosis", "synecdochism", "synopsis", "syphilophobia", "tabbarea",
        "tacheometry", "Tad", "tailband", "talak", "tallowwood", "tamely", "tangleberry", "tantrism", "tappoon", "tariffication", "Tartar", "tasteable", "tauroesque", "taxaspidean", "teachery", "tech", "teet",
        "telecommunication", "telephonist", "tellt", "tempestive", "tendential", "tenontomyoplasty", "tenuous", "terephthalate", "terpadiene", "tertenant", "testoon", "tetradecapod", "tetraploidic", "tetter",
        "thalassiophytous", "that", "Thecophora", "theocratically", "theopneusted", "therese", "thermohyperesthesia", "thersitical", "thightness", "thiolic", "tholi", "thoroughgoing", "threepence", "thronelike",
        "thunderburst", "thymine", "thysanuran", "tidelessness", "tikur", "timeful", "tingi", "Tiphia", "Titanism", "Titus", "todder", "tolerantism", "tomnoddy", "tonous", "topazy", "toran", "torrefy", "tosher",
        "toughish", "Townsendia", "toyish", "trachodont", "traditive", "traitorous", "transcend", "transfuser", "transmissively", "transposal", "trapezius", "treaclewort", "tremblingly", "tret", "tribble",
        "trichinoscopy", "Trichuris", "tridimensional", "trigonite", "trilogist", "trinodine", "tripinnated", "trisazo", "triticeous", "trochaic", "trollopish", "Tropicalia", "Troytown", "trunk", "tryptic",
        "tuberculide", "tubuliform", "tulwar", "tuniness", "turbosupercharger", "turnagain", "turus", "twalt", "twinflower", "Tylerism", "typhoidal", "tyronism", "Uirina", "ultracentrifuge", "ultraoutrageous",
        "umbilical", "unabstract", "unacutely", "unaffliction", "unambush", "unappealable", "unarrestable", "unattempered", "unbailed", "unbefringed", "unbeveled", "unbodied", "unbreezy", "unbuttonment",
        "uncastrated", "uncharged", "uncinctured", "unclip", "uncombed", "uncomposable", "unconfinement", "unconspired", "unconventional", "uncouple", "uncrumple", "undatedness", "undefaced", "undeniably",
        "underbrim", "underdish", "undergoverness", "underlodging", "underpraise", "undershapen", "undersurface", "underwitted", "undiagnosable", "undiscoursed", "undissolving", "undoomed", "unduplicable",
        "unelectrified", "unending", "unepiscopally", "unevenness", "unexhorted", "unextolled", "unfastidious", "unfestival", "unflayed", "unforeknowable", "unfreehold", "unfussy", "unghostly", "ungradual",
        "unguidedly", "unharness", "unheroize", "unhuddle", "unicursal", "uniliteral", "unimposed", "uninfested", "uninsurable", "uninventive", "unispinose", "unjointured", "unknowledgeable", "unleisured",
        "unlizardlike", "unmagnetical", "unmate", "unmeritedness", "unmittened", "unmovingly", "unneedfulness", "unobscene", "unopprobrious", "unpaining", "unpassioned", "unperformed", "unpiercing", "unplug",
        "unpraisable", "unpretermitted", "unpromisingly", "unpublishable", "unquestioningly", "unreasonable", "unreferenced", "unrelinquishable", "unreprieved", "unrestrictive", "unrighted", "unruddled",
        "unsanded", "unschooled", "unseducible", "unshackle", "unshouting", "unsiphon", "unsnagged", "unsoul", "unspontaneous", "unsteadfast", "unstrewed", "unsufferable", "unsurveyable", "untactful",
        "untemptable", "unthriftily", "untotalled", "untrekked", "unturreted", "unvaporized", "unvision", "unwarrantableness", "unwhispered", "unworker", "upbraiding", "upheap", "upright", "upsun", "uranocircite",
        "uredosporiferous", "urfirnis", "uroglaucin", "Urticastrum", "usurpatively", "utterance", "vacual", "Vaidic", "valleyite", "vanessian", "variance", "vasculogenesis", "vaucheriaceous", "vehiculation",
        "venality", "venoauricular", "venture", "verecundness", "Vermont", "versual", "vesicupapular", "vetust", "viceregal", "vigia", "vinaigretted", "vinylene", "virginity", "viscidly", "vitamer", "vive", 
        "voglite", "voltagraphy", "vorlooper", "vuln", "wafermaker", "wainrope", "walleye", "wansonsy", "warluck", "washableness", "watchfulness", "wauf", "waywiser", "weathermaking", "weevily", "wellyard",
        "wetchet", "wheatlike", "whereuntil", "whinger", "whisperless", "whittaw", "wickerwork", "wildcatting", "windable", "wineskin", "wirble", "wistonwish", "wittering", "wolveboon", "woodenware", "woolweed",
         "worldless", "woven", "wright", "wumble", "xanthophore", "xerantic", "xylite", "Yahuna", "yarm", "yellowbird", "yieldingness", "younghearted", "Yurupary", "Zarathustrianism", "Zeppelin", "zinziberaceous",
         "zonal", "zoomagnetic", "zootic", "zygomorphic",};

        auto s2 = std::chrono::steady_clock::now();
        int n = 0;
        for(auto w : test_words)
        {
            EXPECT_TRUE(find(&root, w));
            ++n;
        }
        auto e2 = std::chrono::steady_clock::now();
        std::cout << "Looked up " << n << " words in " << std::chrono::duration_cast<std::chrono::microseconds>(e2 - s2).count() << " us.\n";
    }
}
