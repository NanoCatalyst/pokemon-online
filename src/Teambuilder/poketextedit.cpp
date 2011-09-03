#include "poketextedit.h"
#include "../PokemonInfo/pokemoninfo.h"

QVariant PokeTextEdit::loadResource(int type, const QUrl &name)
{
    if (type != QTextDocument::ImageResource) {
        goto end;
    }

    QString url = name.toString();

    if (url.indexOf(":") <= 0) {
        goto end;
    }

    QString res = name.section(':', 0, 0);

    if (res != "pokemon" && res != "item") {
        goto end;
    }


    QVariant ret;

    if (res == "pokemon") {
        QStringList params = name.section(':', 1).split('&');

        int gen = 5;
        int gender = 0;
        Pokemon::uniqueId num = Pokemon::NoPoke;
        bool shiny=false;
        bool back = false;

        foreach (QString param, params) {
            QString par = param.section('=', 0,0);
            QString val = param.section('=', 1);

            if (par == "gen") {
                gen = val.toInt();
            } else if (par == "num") {
                num = Pokemon::uniqueId(val.section('-', 0,0).toInt(), val.section('-', 1).toInt());
            } else if (par == "shiny") {
                shiny = val == "true";
            } else if (par == "gender") {
                gender = val == "male" ? Pokemon::Male : (val == "female"?Pokemon::Female : Pokemon::Neutral);
            } else if (par == "back") {
                back = val == "true";
            }
        }

        ret = PokemonInfo::Picture(num, gen, gender, shiny, back);
    } else if (res == "item") {
        int item = name.section(':', 1).toInt();
        ret = ItemInfo::Icon(item);
    }

    return ret;

    end:
    return QScrollDownTextBrowser::loadResource(type, name);
}
