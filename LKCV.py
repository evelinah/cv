# rev: 5b8c3b9, exported: 2015-11-26 00:57:21

import os, sys
thisFile = os.path.abspath( __file__ )

if __name__ == '__main__':
    sys.exit( os.system( 'python ' + os.environ[ 'TAU_ROOT' ] + '/build/Hub.py ' + thisFile ) )

# ---------------- #

from build import Constants, Settings

projectName = 'LKCV'
caption = 'LK CV'
publisherInfo = 'Lukasz_Kosakowski'
orientation = Constants.Orientation.Portrait
encryptionKey = '<obfuscated>'
isGame = False

windowsStoreIdentityName = '<obfuscated>'

class BuildConfig:
    TizenBuild = 'tizenBuild'
    BlackberryBuild = 'blackberryBuild'

defaultBuildConfig = { BuildConfig.TizenBuild: False,
                       BuildConfig.BlackberryBuild: False }

version = ( 1, 1, 0 )

# ---------------- #

canvasSize = ( 568, 320 )
longerSideResolution = True
resResolution = 568 * 9
narrowScreenZoomOutFactor = 1
atlasSplitHalves = Constants.AtlasSplitHalves.No

iapEnabled = False
googleAnalyticsTrackingId = '<obfuscated>'

if Settings.platform == Constants.Platform.iOS:
    directResolutions = [ 960, 1024, 1136, 1334, 1920, 2048 ]
    flurryAppKey = '<obfuscated>'
elif Settings.platform == Constants.Platform.Android:
    if Settings.androidBuild == Constants.AndroidBuild.Google:
        directResolutions = [ 480, 800, 854, 1280, 1920, 2560 ]
        flurryAppKey = '<obfuscated>'
    elif Settings.androidBuild == Constants.AndroidBuild.Amazon:
        directResolutions = [ 1024, 1280, 1920, 2560 ]
        flurryAppKey = '<obfuscated>'
    else:
        raise ValueError( 'Unexpected android build: ' + Settings.androidBuild )
elif Settings.platform == Constants.Platform.WindowsPhone:
    directResolutions = [ 800, 1280, 1920 ]
elif Settings.platform == Constants.Platform.Web:
    directResolutions = [ 568, 1136 ]
elif Settings.platform == Constants.Platform.Marmalade:
    if Settings.buildConfig[ BuildConfig.TizenBuild ]:
        directResolutions = [ 800, 1280 ]
    elif Settings.buildConfig[ BuildConfig.BlackberryBuild ]:
        directResolutions = [ 720, 1280, 1440 ]
    else:
        raise ValueError( 'Not specified.' )
elif Settings.platform == Constants.Platform.None_:
    directResolutions = [ 1136 ]
else:
    raise ValueError( 'Not specified.' )

        # (  name         ,  atlas,  fontSource            , fontSize, character set                      )
fonts = [ ( 'debugConsole', 'app' , 'MyriadPro-Regular.ttf', 8       , Constants.CharacterSet.Ascii       ),
          ( 'font9'       , 'menu', 'MyriadPro-Regular.ttf', 9       , Constants.CharacterSet.Ascii       ),
          ( 'font11'      , 'menu', 'MyriadPro-Regular.ttf', 11      , Constants.CharacterSet.Ascii       ),
          ( 'font12'      , 'menu', 'MyriadPro-Regular.ttf', 12      , Constants.CharacterSet.Ascii       ),
          ( 'font13'      , 'menu', 'MyriadPro-Regular.ttf', 13      , Constants.CharacterSet.PolishAscii ),
          ( 'font14'      , 'menu', 'MyriadPro-Regular.ttf', 14      , Constants.CharacterSet.PolishAscii ),
          ( 'font16'      , 'menu', 'MyriadPro-Regular.ttf', 16      , Constants.CharacterSet.PolishAscii ),
          ( 'font18'      , 'menu', 'MyriadPro-Regular.ttf', 18      , Constants.CharacterSet.Ascii       ),
          ( 'font19'      , 'menu', 'MyriadPro-Regular.ttf', 19      , Constants.CharacterSet.Ascii       ),
          ( 'font20'      , 'menu', 'MyriadPro-Regular.ttf', 20      , Constants.CharacterSet.Ascii       ),
          ( 'font22'      , 'menu', 'MyriadPro-Regular.ttf', 22      , Constants.CharacterSet.PolishAscii ) ]
