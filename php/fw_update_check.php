<?PHP
/*Example header data:

[HTTP_USER_AGENT] => ESP-http-Update
[HTTP_X_ESP_STA_MAC] => 18:FE:AA:AA:AA:AA
[HTTP_X_ESP_AP_MAC] => 1A:FE:AA:AA:AA:AA
[HTTP_X_ESP_FREE_SPACE] => 671744
[HTTP_X_ESP_SKETCH_SIZE] => 373940
[HTTP_X_ESP_SKETCH_MD5] => a56f8ef78a0bebd812f62067daf1408a
[HTTP_X_ESP_CHIP_SIZE] => 4194304
[HTTP_X_ESP_SDK_VERSION] => 1.3.0
[HTTP_X_ESP_VERSION] => DOOR-7-g14f53a19
*/
header('Content-type: text/plain; charset=utf8', true);

function check_header($name, $value = false) {
    if(!isset($_SERVER[$name])) {
        return false;
    }
    if($value && $_SERVER[$name] != $value) {
        return false;
    }
    return true;
}

function sendFile($path) {
    header($_SERVER["SERVER_PROTOCOL"].' 200 OK', true, 200);
    header('Content-Type: application/octet-stream', true);
    header('Content-Disposition: attachment; filename='.basename($path));
    header('Content-Length: '.filesize($path), true);
    header('x-MD5: '.md5_file($path), true);
    readfile($path);
}

if(!check_header('HTTP_USER_AGENT', 'ESP-http-Update')) {
    header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
    echo "only for ESP updater!\n";
    exit();
}

if(
    !check_header('HTTP_X_ESP_STA_MAC') ||
    !check_header('HTTP_X_ESP_AP_MAC') ||
    !check_header('HTTP_X_ESP_FREE_SPACE') ||
    !check_header('HTTP_X_ESP_SKETCH_SIZE') ||
    !check_header('HTTP_X_ESP_SKETCH_MD5') ||
    !check_header('HTTP_X_ESP_CHIP_SIZE') ||
    !check_header('HTTP_X_ESP_SDK_VERSION')
) {
    header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
    echo "only for ESP updater! (header)\n";
    exit();
}

$db = array(
    "18:FE:AA:AA:AA:AA" => "DOOR-7-g14f53a19",
    "18:FE:AA:AA:AA:BB" => "TEMP-1.0.0"
);

if(!isset($db[$_SERVER['HTTP_X_ESP_STA_MAC']])) {
    header($_SERVER["SERVER_PROTOCOL"].' 500 ESP MAC not configured for updates', true, 500);
}

$localBinary = "./bin/".$db[$_SERVER['HTTP_X_ESP_STA_MAC']].".bin";

// Check if version has been set and does not match, if not, check if
// MD5 hash between local binary and ESP binary do not match if not.
// then no update has been found.
if((!check_header('HTTP_X_ESP_SDK_VERSION') && $db[$_SERVER['HTTP_X_ESP_STA_MAC']] != $_SERVER['HTTP_X_ESP_VERSION'])
    || $_SERVER["HTTP_X_ESP_SKETCH_MD5"] != md5_file($localBinary)) {
    sendFile($localBinary);
} else {
    header($_SERVER["SERVER_PROTOCOL"].' 304 Not Modified', true, 304);
}

header($_SERVER["SERVER_PROTOCOL"].' 500 no version for ESP MAC', true, 500);