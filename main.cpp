#include <taglib/taglib.h>
#include <taglib/trueaudiofile.h>
#include <taglib/oggflacfile.h>
#include <taglib/wavpackfile.h>
#include <taglib/vorbisfile.h>
#include <taglib/speexfile.h>
#include <taglib/aifffile.h>
#include <taglib/mpegfile.h>
#include <taglib/flacfile.h>
#include <taglib/asffile.h>
#include <taglib/mpcfile.h>
#include <taglib/mp4file.h>
#include <taglib/wavfile.h>
#include <taglib/apefile.h>
#include <taglib/fileref.h>
#include <taglib/modfile.h>
#include <taglib/s3mfile.h>
#include <taglib/itfile.h>
#include <taglib/xmfile.h>
#include <taglib/opusfile.h>

using namespace TagLib;
#define instanceOf(p, t) (dynamic_cast<t *>(&p) == &p)
Ogg::XiphComment *getXiphComment(File &file)
{
    if (instanceOf(file, Ogg::Vorbis::File))
        return ((Ogg::Vorbis::File &)file).tag();
    else if (instanceOf(file, Ogg::FLAC::File))
        return ((Ogg::FLAC::File &)file).tag();
    else if (instanceOf(file, Ogg::Speex::File))
        return ((Ogg::Speex::File &)file).tag();
    else if (instanceOf(file, Ogg::Opus::File))
        return ((Ogg::Opus::File &)file).tag();
    return nullptr;
}

void test_local() {
    auto ref = new FileRef("Z:\\test.xml", false);
    if (ref->isNull())
        std::cout << "Hello" << std::endl;
    delete ref;
}

int main(int argc, char *argv[]) {
	if (argc == 0)
		test_local();
	return 0;
}