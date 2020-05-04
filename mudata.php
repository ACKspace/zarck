<?php
//error_reporting(E_ALL);
//ini_set('display_errors', 1);
//error_reporting(E_NONE);
//ini_set('display_errors', 0);

if( empty( session_id() ) )
    session_start( );

$file = "mudata.json";

// undefined index

// Array of 7 or 8 fields
$indata = json_decode( $_REQUEST["json"], true );

$loc = 0;
$messages = [];
if ( !empty( $indata ) )
{
    $loc = $indata[ 0 ];
    $messages = array_slice( $indata, 7 );
    foreach ( $messages as &$value )
    {
        $value = 'a person says: "' . $value .'"';
    }
    unset($value);

    $indata = array_slice( $indata, 0, 7 );
}
else
{
    $indata = [ 0,0,0,0,0,0,0 ];
}


$outdata = json_decode( file_get_contents( $file ), true );
if ( !$outdata )
    $outdata = [];

$changes = false;

$oldLoc = 0;
$outMessages = [];

// Copy over old information
if( empty( $outdata[ session_id() ] ) )
{
    $outdata[ session_id() ] = [
        "mudata" => $indata,
        "messages" => [],
        "timestamp" => time()
    ];

    $changes = true;
}
else
{
    // Copy over old location
    $oldata = $outdata[ session_id() ];
    $oldLoc = $oldata[ "mudata" ][ 0 ];

    $outMessages = $oldata[ "messages" ];
    $outdata[ session_id() ][ "messages" ] = [];

    // Update data, timestamp
    $outdata[ session_id() ][ "mudata" ] = $indata;
    $outdata[ session_id() ][ "timestamp" ] = time();

    // Timestamp changes!
    //if ( $loc !== $oldLoc || count( $messages ) || count( $outMessages ) )
        $changes = true;
}

// TODO: "status messages" if moved
// Copy over outgoing messages    
//$outMessages = array_slice( $oldata[ "mudata" ], 7 );

if ( $loc !== $oldLoc )
{
    // We moved, clear "chat" messages
    $outMessages = [];

    $amounts = [ 0,0,0,0,0,0,0 ];
    forEach ( $outdata as $sid => $data )
    {
        if ( session_id() === $sid )
            continue;

        for ( $n = 0; $n < 7; $n++ )
            if ( $data["mudata"][0] === $indata[$n] )
                $amounts[ $n ]++;
    }

    for ( $n = 0; $n < 7; $n++ )
    {
        $dir = director( $n, $amounts[$n] );
        if ( $dir )
            $outMessages[] = $dir;
    }
}


// if current user moves or typed a message: store as location infos
$mudata = [];

forEach ( $outdata as $sid => $data )
{
    if ( session_id() === $sid )
        continue;

    if ( time() - $data[ "timestamp" ] > 120 )
    {
        unset( $outdata[ $sid ] );
        continue;
    }

    // Fill array with messages)
    if ( $loc !== $oldLoc )
    {
        $message = "";

        if ( $data[ "mudata" ][ 0 ] === $loc && $oldLoc )
        {
            // Appeared
            $message = "a person just appeared " . directive( $oldLoc, $data[ "mudata" ] );
        }
        else if ( $data[ "mudata" ][ 0 ] === $oldLoc && $loc )
        {
            // Disappeared
            $message = "a person just " . direction( $loc, $data[ "mudata" ] );
        }

        if ( $message )
            $outdata[ $sid ][ "messages" ][] = $message;
    }

    // Copy chat message to user on same location
    if ( $loc === $data[ "mudata" ][ 0 ] && count( $messages ) )
    {
        $outdata[ $sid ][ "messages" ] = array_merge( $data[ "messages" ], $messages );
        $changes = true;
    }
}

    // read post data as json
    // read 'db'

    // store (optional) incoming user message for all users on curloc

    // if oldloc === currentloc
    // read/remove incoming messages from db
    // else
    // store custom message for all users on oldloc

    // remove stale id's (2 minutes idle)

    // write to db/file
    // return json array of combined data minus the current session id one








/*
// Invalid argument supplied
forEach( $delta as $deltask )
{
    $found = false;
    forEach( $mudata as $key => $value )
    {
        if ( $deltask["id"] == $value["id"] )
        {
            if ( $mudata[$key]["done"] != $deltask["done"] )
            {
                $mudata[$key]["done"] = $deltask["done"];
                $changes = true;
            }

            // TODO: barcode array merge + check           
            $mudata[$key]["barcodes"] = array_unique( array_merge( $mudata[$key]["barcodes"], $deltask["barcodes"] ), SORT_REGULAR );


            if ( $mudata[$key]["label"] != $deltask["label"] )
            {
                if ( $deltask["label"] == "" )
                    unset( $mudata[ $key ] );
                else                
                    $mudata[$key]["label"] = $deltask["label"];
                $changes = true;
            }

            $found = true;
        }
    }
    if ( !$found )
    {
        $mudata =  array_merge( $delta, $mudata );
        $changes = true;
    }

}
*/

if ( $changes )
{
    $outdata = json_encode( $outdata, JSON_PRETTY_PRINT );
    $ret = file_put_contents( $file, $outdata );
}

// Align indexes
$outMessages = array_values( $outMessages );
$outMessages = json_encode( $outMessages, JSON_PRETTY_PRINT );
echo $outMessages;


function directive( $_location, $_locations )
{
    // a person just appeared (from {direcion})
    // [the north,the south,the east,the west,above,below]
    if ( $_location === $_locations[ 1 ] )
        return "from the north";
    if ( $_location === $_locations[ 2 ] )
        return "from the south";
    if ( $_location === $_locations[ 3 ] )
        return "from the east";
    if ( $_location === $_locations[ 4 ] )
        return "from the west";
    if ( $_location === $_locations[ 5 ] )
        return "from above";
    if ( $_location === $_locations[ 6 ] )
        return "from below";

    return "";
}

function direction( $_location, $_locations )
{
    // a person just disappeared
    // a person just went {direction}
    // [north,south,east,west,up,down]
    if ( $_location === $_locations[ 1 ] )
        return "went north";
    if ( $_location === $_locations[ 2 ] )
        return "went south";
    if ( $_location === $_locations[ 3 ] )
        return "went east";
    if ( $_location === $_locations[ 4 ] )
        return "went west";
    if ( $_location === $_locations[ 5 ] )
        return "went up";
    if ( $_location === $_locations[ 6 ] )
        return "went down";

    return "disappeared";
}

function director( $_location, $_amount )
{
    if ( !$_amount )
        return "";

    $message = "there ";

    if ( $_location > 4 )
    {
        $message .= "seems to be someone ".($_location===5?"above":"below");
    }
    else
    {
        if ( $_amount === 1 )
            $message .= "is a person";
        else
            $message .= "are ".$amounts[ 0 ]." persons";

        if ( !$_location )
            $message .= " standing next to";
        else if ( $_location === 1 )
            $message .= " north of";
        else if ( $_location === 2 )
            $message .= " south of";
        else if ( $_location === 3 )
            $message .= " east of";
        else if ( $_location === 4 )
            $message .= " west of";
    }
    $message .= " you";

    /*
    there {is a person|are n persons|seems to be someone} (standing) {next to|{north|south|east|west} of|above|below} you


    there {is a person|are n persons} standing {direction} you
    next to
    [north,south,east,west] of

    there seems to be someone {direction} you
    above
    below
    */

    return $message;
}

?>

