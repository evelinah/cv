# rev: 89281ca, exported: 2015-10-16 23:24:12

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

version = ( 1, 0, 0 )

# ---------------- #

resResolution = 2880
narrowScreenZoomOutFactor = 1

if Settings.platform == Constants.Platform.iOS:
    directResolutions = [ 640, 750, 1080, 1152 ]
elif Settings.platform == Constants.Platform.Android:
    if Settings.androidBuild == Constants.AndroidBuild.Google:
        directResolutions = [ 320, 480, 720, 1080, 1440, 1600 ]
    elif Settings.androidBuild == Constants.AndroidBuild.Amazon:
        directResolutions = [ 600, 800, 1200, 1600 ]
    else:
        raise ValueError( 'Unexpected android build: ' + Settings.androidBuild )
elif Settings.platform == Constants.Platform.WindowsPhone:
    directResolutions = [ 450, 720, 1080 ]
elif Settings.platform == Constants.Platform.None_:
    directResolutions = [ 640 ]

        # (  name         ,  atlas,  fontSource            , fontSize @ designResolution, character set                      )
fonts = [ ( 'debugConsole', 'app' , 'MyriadPro-Regular.ttf', 8                          , Constants.CharacterSet.Ascii       ),
          ( 'font9'       , 'menu', 'MyriadPro-Regular.ttf', 9                          , Constants.CharacterSet.Ascii       ),
          ( 'font11'      , 'menu', 'MyriadPro-Regular.ttf', 11                         , Constants.CharacterSet.Ascii       ),
          ( 'font12'      , 'menu', 'MyriadPro-Regular.ttf', 12                         , Constants.CharacterSet.Ascii       ),
          ( 'font13'      , 'menu', 'MyriadPro-Regular.ttf', 13                         , Constants.CharacterSet.PolishAscii ),
          ( 'font14'      , 'menu', 'MyriadPro-Regular.ttf', 14                         , Constants.CharacterSet.PolishAscii ),
          ( 'font16'      , 'menu', 'MyriadPro-Regular.ttf', 16                         , Constants.CharacterSet.PolishAscii ),
          ( 'font18'      , 'menu', 'MyriadPro-Regular.ttf', 18                         , Constants.CharacterSet.Ascii       ),
          ( 'font19'      , 'menu', 'MyriadPro-Regular.ttf', 19                         , Constants.CharacterSet.Ascii       ),
          ( 'font20'      , 'menu', 'MyriadPro-Regular.ttf', 20                         , Constants.CharacterSet.Ascii       ),
          ( 'font22'      , 'menu', 'MyriadPro-Regular.ttf', 22                         , Constants.CharacterSet.PolishAscii ) ]

atlasSplitHalves = Constants.AtlasSplitHalves.No

# ---------------- #

flurryAppKey = '<obfuscated>'
googleAnalyticsTrackingId = '<obfuscated>'

iapEnabled = False
