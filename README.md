<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8"/>
	<title></title>
	<meta name="generator" content="LibreOffice 6.0.7.3 (Linux)"/>
	<meta name="created" content="00:00:00"/>
	<meta name="changed" content="2019-08-03T16:25:42.537179541"/>
	<style type="text/css">
		@page { margin: 2cm }
		p { margin-bottom: 0.25cm; line-height: 115% }
	</style>
</head>
<body lang="en-GB" dir="ltr">
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Noto Mono">This
project provides a Battery Protection System (<b>BPS</b>) for 4S
LifePo4 banks.  It was developed for a 3p4s bank of prismatic cells
totalling 540Ah.</font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Noto Mono"><b>What’s
a BPS?</b>  Its simply a system designed to protect the battery bank
from the user.  In short, it monitors the bank for ‘out of
tolerance’ events and will take the appropriate action. It is not a
Battery Management System (whatever that is) – there is no form of
active or passive cell balancing since, using good cells that are top
balanced on installation, little if any subsequent balancing should
be necessary.</font></p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><font face="Noto Mono"><b>Features:</b></font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	ESP32</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	MQTT output for remote monitoring</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	ADC noise, 4mV</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	Programmable warning and cutoff thresholds</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	Over and under voltage thresholds at cell and
bank level</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	Maximum cell differential voltage thresholds</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	6 channel, 4A relay drivers</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	Programmable for latching or normal relays</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	4 additonal 3v3 inputs/outputs for triggering
other events</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	Temperature monitoring (DS18b20)</font></p>
<p style="margin-bottom: 0cm; font-weight: normal; line-height: 100%">
<font face="Noto Mono">	 </font>
</p>
</body>
</html>