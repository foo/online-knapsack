#!/usr/bin/perl -l

use strict;

sub compute {
	my ($xi,$eps,$t) = @_;
	my $twothirds = 2/3;
	my $twothirdseps = $twothirds + $eps;

	open O, ">tmp.lp";
	print O "max: r;";
	print O "r <= " . ($xi/3) . " + $t * c2 + " . ($twothirds * (1-$xi)) . " - $twothirds * c2;";		# R1
	print O "r <= 0.5 * c1 + $t * c - $t * c1 + $twothirdseps - $twothirdseps * c;"; # R2
	print O "r <= " . (5/6) * $xi . " + 0.5 * c1 + $t * c - $t * c1 + $twothirds - $twothirds * c - " . ($twothirds * $xi) . ";"; # R3
	print O "r <= " . (0.5/$t) . " * c1;"; # R4
	print O "r <= " . ($t/$twothirdseps) . " * c2;"; # R5
	print O "r <= " . (0.5/$twothirdseps) . " * c1 + " . ($t/$twothirdseps) . " * c - " . ($t/$twothirdseps) . " * c1;"; # R5

	print O "c1 <= 1;";
	print O "c2 <= 1;";
	print O "c <= 1;";
	print O "c <= c1 + c2;";
	print O "c >= c1;";
	print O "c >= c2;";
	close O;
	
	my $output = `lp_solve -S1 < tmp.lp`;
	my ($result) = ($output =~ /Value of objective function: (.*)/);
	return $result;
}

my $bestratio = 2;
my $steps = 100; 
my ($xi_low, $xi_high) =   (0.106-0.01, 0.106+0.01);
my ($eps_low, $eps_high) = (0.108-0.01, 0.108+0.01);
#my ($t_low, $t_high) =     (0.613-0.02, 0.613+0.02);

for (my $xi =$xi_low;  $xi <=$xi_high;  $xi +=($xi_high-$xi_low)  /$steps) {
for (my $eps=$eps_low; $eps<=$eps_high; $eps+=($eps_high-$eps_low)/$steps) {
#for (my $t  =$t_low;   $t  <=$t_high;   $t  +=($t_high-$t_low)    /$steps) {
#	next if ($t + $eps/2 + 1/3 > 1);	# C1 and S have to always fit together 
	my $t = 2/3 - $eps/2;
	my $ratio = 1/compute ($xi,$eps,$t);
	if ($bestratio > $ratio) {
		$bestratio = $ratio;
		print "$bestratio for xi=$xi, eps=$eps, t=$t";
	}
}}



