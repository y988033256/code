<!doctype html>
<html lang="en">
<head>
    <link  rel="stylesheet" type="text/css" href="index.css"/>
    <meta charset="UTF-8" />
    <title>Admin</title>
</head>
<body>
<div class="header">
    <p>Admin Page</p>
</div>
<div class="navbar">
    <ul>
        <li><a href="index.html">Home</a></li>
        <li><a href="viewEventsPage.php">View events</a></li>
        <li><a href="admin.php">Admin</a></li>
        <li><a href="Credits.html">Credits</a></li>
        <li><a href="addEventForm.php">Add Event</a></li>
    </ul>
</div>
<?php
include 'database_conn.php';   //Connect to the server
$sql = "SELECT eventID,eventTitle, eventDescription,venueName,catDesc, eventStartDate,eventEndDate, eventPrice
FROM AE_events 
INNER JOIN AE_category 
ON AE_category.catID = AE_events.catID 
INNER JOIN AE_venue
ON AE_venue.venueID = AE_events. venueID
ORDER BY eventTitle";                                            //Construct an SQL query
$queryResult = $dbConn->query($sql);                  //Execute the query and store the result set
if($queryResult === false)
{
    echo "<p>Query failed: ".$dbConn->error."</p>";
    exit;
}
else
    {
        echo "<div class='EventTitle'>
                  <span class='Title'>Title</span>
                  <span class='adminDescription'>Description</span>
                  <span class='Venue'>Venue</span>
                  <span class='Category'>Category</span>
                  <span class='SDate'>Start Date</span>
                  <span class='EDate'>End Date</span>
                  <span class='EventPrice'>Price(£)</span>
                  <span class='Button'></span>
              </div>\n";
        While($rowObj = $queryResult->fetch_object())               //Iterate over that result set Extract each record  and Display it
        {                                                                    // display all the detail of the events
            echo "<div class='Event'>                                            
                      <span class='Title'>{$rowObj->eventTitle}</span>
                      <span class='adminDescription'>{$rowObj->eventDescription}</span>
                      <span class='Venue'>{$rowObj->venueName}</span>
                      <span class='Category'>{$rowObj->catDesc}</span>
                      <span class='SDate'>{$rowObj->eventStartDate}</span>
                      <span class='EDate'>{$rowObj->eventEndDate}</span>
                      <span class='EventPrice'>{$rowObj->eventPrice}</span>                 
                      <span class='Button'><a href='editEvents.php?eventID={$rowObj->eventID}'><input type='submit' value= 'Edit' /></a></span>
                  </div>\n";
        }
    }
$queryResult->close();
$dbConn->close();
?>
</body>
</html>
