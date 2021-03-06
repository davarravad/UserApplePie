<?php

//Calculate percentages
function percent($num_prev, $num_current) {
	// Calculate the percentage
	$percent_total = number_format(((1 - $num_prev / $num_current) * 100), 2); // yields 0.76
	// Check if there is an increase or decrease
	if($percent_total == "0"){
		$percent_display = "<font color=green>$percent_total</font>";
	}else if($percent_total < 0){
		// There is a decrease
		$percent_total_minus = number_format(abs($percent_total),2);
		$percent_display = " <i class='glyphicon glyphicon-chevron-down text-danger'></i> <font color=red>$percent_total_minus</font>";
	}else{
		// There is an increase
		$percent_display = " <i class='glyphicon glyphicon-chevron-up text-success'></i> <font color=green>$percent_total</font>";
	}
	echo $percent_display;
}

//////////////////////////////////////////Unique Visitors//////////////////////////////////////
//Get total number of unique visitors today
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where DATE(`timestamp`) = CURDATE() "); 
$result->execute();
$total_visitors_today = $result->fetchColumn(0);
//echo $total_visitors_today;
unset($result);

//Get total number of unique visitors yesterday
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where timestamp BETWEEN DATE_ADD(CURDATE(), INTERVAL -1 day) AND CURDATE()"); 
$result->execute();
$total_visitors_yesterday = $result->fetchColumn(0);
//echo $total_visitors_yesterday;
unset($result);

// Get total number of unique visitors this week
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where timestamp > DATE_SUB(NOW(), INTERVAL 1 WEEK)"); 
$result->execute();
$total_visitors_week = $result->fetchColumn(0);
//echo $total_visitors_week;
unset($result);

//Get total number of unique visitors last week
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where WEEK(`timestamp`) = WEEK(DATE_SUB(CURDATE(), INTERVAL 1 WEEK)) "); 
$result->execute();
$total_visitors_lastweek = $result->fetchColumn(0);
//echo $total_visitors_lastweek;
unset($result);

// Get total number of unique visitors this month
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where timestamp > DATE_SUB(NOW(), INTERVAL 1 MONTH)"); 
$result->execute();
$total_visitors_month = $result->fetchColumn(0);
//echo $total_visitors_month;
unset($result);

//Get total number of unique visitors last month
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where MONTH(`timestamp`) = MONTH(DATE_SUB(CURDATE(), INTERVAL 1 MONTH)) "); 
$result->execute();
$total_visitors_lastmonth = $result->fetchColumn(0);
//echo $total_visitors_lastmonth;
unset($result);

// Get total number of unique visitors this year
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where timestamp > DATE_SUB(NOW(), INTERVAL 1 YEAR)"); 
$result->execute();
$total_visitors_year = $result->fetchColumn(0);
//echo $total_visitors_year;
unset($result);

//Get total number of unique visitors last year
$result = $DBH->prepare("select count(distinct ipaddy) from ".$db_table_prefix."sitelogs where YEAR(`timestamp`) = YEAR(DATE_SUB(CURDATE(), INTERVAL 1 YEAR))"); 
$result->execute();
$total_visitors_lastyear = $result->fetchColumn(0);
//echo $total_visitors_lastyear;
unset($result);

//////////////////////////////////////////Page Views//////////////////////////////////////
//Get total number of unique visitors today
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where DATE(`timestamp`) = CURDATE()"); 
$result->execute();
$total_page_views_today = $result->fetchColumn(0);
//echo $total_page_views_today;
unset($result);

//Get total number of unique visitors yesterday
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where timestamp BETWEEN DATE_ADD(CURDATE(), INTERVAL -1 day) AND CURDATE()"); 
$result->execute();
$total_page_views_yesterday = $result->fetchColumn(0);
//echo $total_page_views_yesterday;
unset($result);

// Get total number of unique visitors this week
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where timestamp > DATE_SUB(NOW(), INTERVAL 1 WEEK)"); 
$result->execute();
$total_page_views_week = $result->fetchColumn(0);
//echo $total_page_views_week;
unset($result);

//Get total number of unique visitors last week
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where WEEK(`timestamp`) = WEEK(DATE_SUB(CURDATE(), INTERVAL 1 WEEK))"); 
$result->execute();
$total_page_views_lastweek = $result->fetchColumn(0);
//echo $total_page_views_lastweek;
unset($result);

// Get total number of unique visitors this month
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where timestamp > DATE_SUB(NOW(), INTERVAL 1 MONTH)"); 
$result->execute();
$total_page_views_month = $result->fetchColumn(0);
//echo $total_page_views_month;
unset($result);

//Get total number of unique visitors last month
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where MONTH(`timestamp`) = MONTH(DATE_SUB(CURDATE(), INTERVAL 1 MONTH))"); 
$result->execute();
$total_page_views_lastmonth = $result->fetchColumn(0);
//echo $total_page_views_lastmonth;
unset($result);

// Get total number of unique visitors this year
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where timestamp > DATE_SUB(NOW(), INTERVAL 1 YEAR)"); 
$result->execute();
$total_page_views_year = $result->fetchColumn(0);
//echo $total_page_views_year;
unset($result);

//Get total number of unique visitors last year
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."sitelogs where YEAR(`timestamp`) = YEAR(DATE_SUB(CURDATE(), INTERVAL 1 YEAR))"); 
$result->execute();
$total_page_views_lastyear = $result->fetchColumn(0);
//echo $total_page_views_lastyear;
unset($result);

// Get total number of support tickets
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."report"); 
$result->execute();
$total_support_tickets = $result->fetchColumn(0);
//echo $total_page_views_lastyear;
unset($result);

// Get total number of support tickets
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."errors"); 
$result->execute();
$total_site_errors = $result->fetchColumn(0);
//echo $total_page_views_lastyear;
unset($result);

// Get total number of support tickets
$result = $DBH->prepare("select count(*) from ".$db_table_prefix."users"); 
$result->execute();
$total_site_members = $result->fetchColumn(0);
//echo $total_page_views_lastyear;
unset($result);

?>

                <!-- Page Heading -->
                <div class='row'>
                    <div class='col-lg-12'>
                        <h1 class='page-header'>
                            Dashboard <small>Statistics Overview</small>
                        </h1>
                        <ol class='breadcrumb'>
							<li>
								<i class='glyphicon glyphicon-cog'></i> Admin Panel
							</li>
                            <li class='active'>
                                <i class='fa fa-dashboard'></i> Dashboard
                            </li>
                        </ol>
                    </div>
                </div>
                <!-- /.row -->

				<div class='row'>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-info'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-user'></i> Visitors Today!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_visitors_today;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_visitors_yesterday;
												//echo "<Br>";
												percent($total_visitors_yesterday, $total_visitors_today);
												echo "% From Yesterday";
											?>
                            </div>
                        </div>
                    </div>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-info'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-user'></i> Visitors This Week!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_visitors_week;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_visitors_lastweek;
												//echo "<Br>";
												percent($total_visitors_lastweek, $total_visitors_week);
												echo "% From Last Week";
											?>
                            </div>
                        </div>
                    </div>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-info'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-user'></i> Visitors This Month!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_visitors_month;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_visitors_lastmonth;
												//echo "<Br>";
												percent($total_visitors_lastmonth, $total_visitors_month);
												echo "% From Last Month";
											?>
                            </div>
                        </div>
                    </div>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-info'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-user'></i> Visitors This Year!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_visitors_year;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_visitors_lastyear;
												//echo "<Br>";
												percent($total_visitors_lastyear, $total_visitors_year);
												echo "% From Last Year";
											?>
                            </div>
                        </div>
                    </div>
                </div>
                <!-- /.row -->
				
			
				<div class='row'>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-default'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-file'></i> Page Views Today!
										<div class='huge'>
											<?php
												// Display total unique Page Views today
												echo $total_page_views_today;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_page_views_yesterday;
												//echo "<Br>";
												percent($total_page_views_yesterday, $total_page_views_today);
												echo "% From Yesterday";
											?>
                            </div>
                        </div>
                    </div>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-default'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-file'></i> Page Views This Week!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_page_views_week;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_page_views_lastweek;
												//echo "<Br>";
												percent($total_page_views_lastweek, $total_page_views_week);
												echo "% From Last Week";
											?>
                            </div>
                        </div>
                    </div>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-default'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-file'></i> Page Views This Month!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_page_views_month;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_page_views_lastmonth;
												//echo "<Br>";
												percent($total_page_views_lastmonth, $total_page_views_month);
												echo "% From Last Month";
											?>
                            </div>
                        </div>
                    </div>
					<div class='col-lg-3 col-md-3 col-sm-6'>
                        <div class='panel panel-default'>
                            <div class='panel-heading' style='text-align: center'>
                                        <i class='glyphicon glyphicon-file'></i> Page Views This Year!
										<div class='huge'>
											<?php
												// Display total unique visitors today
												echo $total_page_views_year;
											?>
										</div>
											<?php
												// Display percentage compaired to yesterday
												//echo $total_page_views_lastyear;
												//echo "<Br>";
												percent($total_page_views_lastyear, $total_page_views_year);
												echo "% From Last Year";
											?>
                            </div>
                        </div>
                    </div>
                </div>
                <!-- /.row -->			
			
				
                <div class='row'>
                    <div class='col-lg-4 col-md-4'>
                        <div class='panel panel-primary'>
                            <div class='panel-heading'>
                                <div class='row'>
                                    <div class='col-xs-3'>
                                        <i class='fa fa-comments fa-5x'></i>
                                    </div>
                                    <div class='col-xs-9 text-right'>
                                        <div class='huge'>
										<?php
											echo $total_site_members;
										?>
										</div>
                                        <div>Site Members!</div>
                                    </div>
                                </div>
                            </div>
							<?php 
								echo "<a href='".$websiteUrl."UAP_Admin_Panel/admin_users/'>";
							?>
                                <div class='panel-footer'>
                                    <span class='pull-left'>View Details</span>
                                    <span class='pull-right'><i class='fa fa-arrow-circle-right'></i></span>
                                    <div class='clearfix'></div>
                                </div>
                            </a>
                        </div>
                    </div>
                    <div class='col-lg-4 col-md-4'>
                        <div class='panel panel-red'>
                            <div class='panel-heading'>
                                <div class='row'>
                                    <div class='col-xs-3'>
                                        <i class='fa fa-support fa-5x'></i>
                                    </div>
                                    <div class='col-xs-9 text-right'>
                                        <div class='huge'>
										<?php
											echo $total_site_errors;
										?>
										</div>
                                        <div>Site Errors!</div>
                                    </div>
                                </div>
                            </div>
							<?php 
								echo "<a href='".$websiteUrl."UAP_Admin_Panel/errors/'>";
							?>
                                <div class='panel-footer'>
                                    <span class='pull-left'>View Details</span>
                                    <span class='pull-right'><i class='fa fa-arrow-circle-right'></i></span>
                                    <div class='clearfix'></div>
                                </div>
                            </a>
                        </div>
                    </div>
        
                    <div class='col-lg-4 col-md-4'>
                        <div class='panel panel-green'>
                            <div class='panel-heading'>
                                <div class='row'>
                                    <div class='col-xs-3'>
                                        <i class='fa fa-tasks fa-5x'></i>
                                    </div>
                                    <div class='col-xs-9 text-right'>
                                        <div class='huge'>
											<?php
												echo $total_support_tickets;
											?>
										</div>
                                        <div>Support Tickets!</div>
                                    </div>
                                </div>
                            </div>
							<?php 
								echo "<a href='".$websiteUrl."UAP_Admin_Panel/reports/'>";
							?>
                                <div class='panel-footer'>
                                    <span class='pull-left'>View Details</span>
                                    <span class='pull-right'><i class='fa fa-arrow-circle-right'></i></span>
                                    <div class='clearfix'></div>
                                </div>
                            </a>
                        </div>
                    </div>
                </div>
                <!-- /.row -->
