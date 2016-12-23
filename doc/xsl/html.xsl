<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html"/>

<xsl:template match="/">
	<xsl:apply-templates select="document"/>
</xsl:template>

<xsl:template match="annotation"/>

<xsl:template match="document">
<html lang="{@xml:lang}">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<title><xsl:value-of select="title"/></title>
<style type="text/css">
body {
	font-family: verdana, sans-serif;
	font-size: 10pt;
    background-color: #777777;
    margin: 0;
}
div.page-wrap {
    background-color: white;
    width: 210mm; /* A4 */
    margin: 0 auto;
    padding: 2mm 5mm;
}
p, div {
	margin-top: 6pt;
	margin-bottom: 0;
}
h1, h2, h3, h4, h5, h6 {
	font-weight: bold;
	margin-top: 9pt;
	margin-bottom: 12pt;
	margin-left: 0;
}
h1 { font-size: 16pt; }
h2 { font-size: 13pt; }
h3 { font-size: 11pt; }
h4 { font-size: 11pt; }
span.h1_num, span.h2_num {
	margin-right: 2em;
	font-family: sans-serif;
}
span.h3_num, span.h4_num {
	margin-right: 2em;
	font-weight: normal;
	font-size: smaller;
}
h1.main-title {
	font-size: 2em;
	font-weight: bold;
}
a.toc { text-decoration: none; }
a.toc:hover { text-decoration: underline; }
pre.code {
	background-color: #EEE;
	border: 1px solid #CCCCCC;
	padding-top: 6pt;
	padding-bottom: 6pt;
	padding-left: 2pt;
	font-family: monospace;
	font-size: 10pt;
	width: 16.5cm;
}
pre.prototype {
	font-family: monospace;
	margin-top: 0;
	margin-bottom: 0;
}
div.section {
	font-weight: bold;
}
div.todo {
	color: red;
	font-weight: bold;
}
span.ver {
	font-size: smaller;
	color: #C0C0C0;
}
span.nonterminal {
	font-family: monospace;
	font-style: italic;
}
span.sign {
	color: #C0C0C0;
	font-family: monospace;
	font-size: 9pt;
	font-weight: bold;
}
blockquote {
	margin-top: 6pt;
	margin-bottom: 0;
	margin-right: 0;
}
blockquote * {
	margin-top: 0;
	margin-bottom: 0;
}
</style>
</head>
<body>
    <div class="page-wrap">
        <xsl:apply-templates select="title" mode="document"/>
        <xsl:call-template name="toc"/>
        <xsl:apply-templates>
            <xsl:with-param name="chapter_level" select="1"/>
        </xsl:apply-templates>
    </div>
</body>
</html>
</xsl:template>

<xsl:template match="chapter">
	<xsl:param name="chapter_level"/>
	<xsl:param name="chapter_prefix"/>

	<!-- Detect position of the current chapter relatively sibling chapters -->
	<xsl:variable name="my-id" select="generate-id()"/>
	<xsl:variable name="pos">
		<xsl:for-each select="../chapter">
			<xsl:if test="generate-id() = $my-id">
				<xsl:value-of select="position()"/>
			</xsl:if>
		</xsl:for-each>
	</xsl:variable>

	<xsl:apply-templates select="title" mode="chapter">
		<xsl:with-param name="level" select="$chapter_level"/>
		<xsl:with-param name="no" select="concat($chapter_prefix, $pos)"/>
	</xsl:apply-templates>
	<xsl:apply-templates>
		<xsl:with-param name="chapter_level" select="$chapter_level+1"/>
		<xsl:with-param name="chapter_prefix" select="concat($chapter_prefix, $pos, '.')"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template name="toc">
	<table style="font-size:10pt;" cellspacing="0" cellpadding="0">
		<caption style="text-align:left"><h2>Contents</h2></caption>
		<xsl:call-template name="toc-entry"/>
	</table>
</xsl:template>

<xsl:template name="toc-entry">
	<xsl:param name="prefix"/>
	<xsl:param name="level" select="1"/>

	<xsl:for-each select="chapter">
		<tr>
			<td style="padding-right:1ex">
				<xsl:value-of select="concat($prefix, position())"/>
			</td>
			<td>
				<xsl:if test="$level > 2">
					<xsl:attribute name="style">padding-left:4ex</xsl:attribute>
				</xsl:if>
				<a class="toc" href="#chapter-{translate(concat($prefix, position()),'.','_')}">
					<xsl:apply-templates select="title" mode="toc"/>
				</a>
			</td>
		</tr>
		<xsl:call-template name="toc-entry">
			<xsl:with-param name="prefix" select="concat($prefix, position(), '.')"/>
			<xsl:with-param name="level" select="$level + 1"/>
		</xsl:call-template>
		<xsl:if test="$level = 1">
			<!-- Space between level 1 chapters -->
			<tr><td colspan="2" style="font-size:5pt;">&#xA0;</td></tr>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

<xsl:template match="title"/>

<xsl:template match="title" mode="document">
	<h1 class="main-title">
		<xsl:apply-templates/>
		<xsl:if test="/document/@version">
			<span class="ver">
				<xsl:value-of select="concat(' v', /document/@version)"/>
				<xsl:if test="/document/@status and /document/@status != 'Release'">
					<xsl:value-of select="concat(' [', /document/@status, ']')"/>
				</xsl:if>
			</span>
		</xsl:if>
	</h1>
</xsl:template>

<xsl:template match="title" mode="chapter">
	<xsl:param name="level"/>
	<xsl:param name="no"/>

	<xsl:element name="h{$level}">
		<span class="h{$level}_num"><xsl:value-of select="$no"/></span>
		<a id="chapter-{translate($no,'.','_')}"/>
		<xsl:apply-templates/>
	</xsl:element>
</xsl:template>

<xsl:template match="title" mode="section">
	<div class="section"><xsl:apply-templates/></div>
</xsl:template>

<xsl:template match="title" mode="toc">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="p">
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="tt">
	<tt><xsl:apply-templates/></tt>
</xsl:template>

<xsl:template match="u">
	<u><xsl:apply-templates/></u>
</xsl:template>

<xsl:template match="b">
	<b><xsl:apply-templates/></b>
</xsl:template>

<xsl:template match="nt">
	<span class="nonterminal"><xsl:apply-templates/></span>
</xsl:template>

<xsl:template match="list[@style='numbered']">
	<ol>
		<xsl:for-each select="item">
			<li><xsl:apply-templates/></li>
		</xsl:for-each>
	</ol>
</xsl:template>

<xsl:template match="list[@style='bulleted']">
	<ul>
		<xsl:for-each select="item">
			<li><xsl:apply-templates/></li>
		</xsl:for-each>
	</ul>
</xsl:template>

<xsl:template match="list[@style='nomarks']">
	<ul style="list-style-type:none">
		<xsl:for-each select="item">
			<li><xsl:apply-templates/></li>
		</xsl:for-each>
	</ul>
</xsl:template>

<xsl:template match="list">
	<div class="todo">Invalid list style</div>
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="link">
	<a href="{.}"><xsl:apply-templates/></a>
</xsl:template>

<xsl:template match="link[@href]">
	<a href="{@href}"><xsl:apply-templates/></a>
</xsl:template>

<xsl:template match="code-block | tty">
	<pre class="code"><xsl:apply-templates/></pre>
</xsl:template>

<xsl:template match="section">
	<xsl:apply-templates select="title" mode="section"/>
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="note">
	<div><u><b>Note</b></u>: <xsl:apply-templates/></div>
</xsl:template>

<xsl:template match="note[parent::synopsis]">
	<div><u>Note</u>: <xsl:apply-templates/></div>
</xsl:template>

<xsl:template match="precondition">
	<div><u>Precondition</u>: <xsl:apply-templates/></div>
</xsl:template>

<xsl:template match="postcondition">
	<div><u>Postcondition</u>: <xsl:apply-templates/></div>
</xsl:template>

<xsl:template match="invariant">
	<div><u>Invariant</u>: <xsl:apply-templates/></div>
</xsl:template>

<xsl:template match="synopsis">
	<div>
		<xsl:apply-templates select="prototype" mode="synopsis"/>
		<blockquote><xsl:apply-templates/></blockquote>
	</div>
</xsl:template>

<xsl:template match="prototype"/>
<xsl:template match="prototype" mode="synopsis">
	<pre class="prototype"><xsl:apply-templates/></pre>
</xsl:template>

<xsl:template match="sign">
	<span class="sign">[<xsl:apply-templates/>]</span>
</xsl:template>

<xsl:template match="TODO">
	<div class="todo">[TODO<xsl:if test="string(.)">: <xsl:value-of select="."/>
		</xsl:if>]</div>
</xsl:template>

</xsl:stylesheet>
