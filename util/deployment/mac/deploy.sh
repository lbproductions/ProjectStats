
PWD=$1
OUT_PWD=$2
DEPLOY_DIR='/Users/niclasaabe/Dropbox/Public/ProjectStats'

VERSION=`cd $PWD && /usr/local/git/bin/git describe --tags`

macdeployqt $OUT_PWD/ProjectStats.app
cp -r /Library/Frameworks/Sparkle.framework $OUT_PWD/ProjectStats.app/Contents/Frameworks
cp $PWD/Ressources/Icons/projectstats.icns $OUT_PWD/ProjectStats.app/Contents/Resources/
sed 's/\[VERSION\]/'$VERSION'/g' $PWD/Info.plist > $OUT_PWD/ProjectStats.app/Contents/Info.plist
cp $PWD/Updater/dsa_pub.pem $OUT_PWD/ProjectStats.app/Contents/Resources/
cp -r $OUT_PWD/ProjectStats.app $DEPLOY_DIR
cp $PWD/Updater/ProjectStatsAppCast.xml $DEPLOY_DIR/ProjectStatsAppCast.tmp.xml
sed 's/\[VERSION\]/'$VERSION'/g' $DEPLOY_DIR/ProjectStatsAppCast.tmp.xml > $DEPLOY_DIR/ProjectStatsAppCast.tmp2.xml
cp $PWD/projectstats_*.qm $OUT_PWD/ProjectStats.app/Contents/Resources/

cd $DEPLOY_DIR
zip ProjectStats.zip -r ProjectStats.app
cd -

DSASIGNATURE=`ruby $PWD/Updater/sign_update.rb $DEPLOY_DIR/ProjectStats.zip ~/.ssh/dsa_priv.pem`
sed 's#\[DSASIGNATURE\]#'$DSASIGNATURE'#g' $DEPLOY_DIR/ProjectStatsAppCast.tmp2.xml > $DEPLOY_DIR/ProjectStatsAppCast.tmp3.xml

sed 's#\[DATE\]#'"`date`"'#g' $DEPLOY_DIR/ProjectStatsAppCast.tmp3.xml > $DEPLOY_DIR/ProjectStatsAppCast.tmp4.xml
sed 's#\[LENGTH]#'"`du $DEPLOY_DIR/ProjectStats.zip | sed 's/\([0-9]*\)\(.*\)/\1/'`"'#g' $DEPLOY_DIR/ProjectStatsAppCast.tmp4.xml > $DEPLOY_DIR/ProjectStatsAppCast.xml

rm $DEPLOY_DIR/ProjectStatsAppCast.tmp.xml
rm $DEPLOY_DIR/ProjectStatsAppCast.tmp2.xml
rm $DEPLOY_DIR/ProjectStatsAppCast.tmp3.xml
rm $DEPLOY_DIR/ProjectStatsAppCast.tmp4.xml

cp $PWD/Updater/rnotes.html $DEPLOY_DIR
cp $PWD/Updater/rnotes.css $DEPLOY_DIR
