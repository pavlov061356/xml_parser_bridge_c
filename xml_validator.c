#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include "xml_validator.h"

static void schemaParseErrorHandler(void *arg, xmlErrorPtr error)
{
    fprintf(stderr, "Error at line %d, column %d\n%s", error->line, error->int2, error->message);
    *((bool *)arg) = true;
}

char *validateXml(char *xmlPath, char *xsdPath)
{
    xmlInitParser();
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr schema_parser_ctxt = NULL;
    int has_schema_errors = 0;
    int ret = -1;
    xmlSchemaValidCtxtPtr valid_ctxt = NULL;
    if ((schema_parser_ctxt = xmlSchemaNewParserCtxt(xsdPath)))
    {
        schema = xmlSchemaParse(schema_parser_ctxt);
        xmlSchemaFreeParserCtxt(schema_parser_ctxt);
        if (schema)
        {
            valid_ctxt = xmlSchemaNewValidCtxt(schema);
        }
    }
    xmlTextReaderPtr reader = NULL;
    reader = xmlReaderForFile(xmlPath, NULL, 0);

    if (reader != NULL)
    {
        if (valid_ctxt)
        {
            xmlTextReaderSchemaValidateCtxt(reader, valid_ctxt, 0);
            xmlSchemaSetValidStructuredErrors(valid_ctxt, schemaParseErrorHandler, &has_schema_errors);
        }
        ret = xmlTextReaderRead(reader);
        while (ret == 1 && !has_schema_errors)
        {
            //... procesing informations
            ret = xmlTextReaderRead(reader);
        }
    }

    char *buf = malloc(sizeof(char) * 1000);
    ;

    if (ret != 0)
    {
        xmlErrorPtr err = xmlGetLastError();
        sprintf(buf, "%s: failed to parse in line %d, col %d. Error %d: %s\n",
                err->file,
                err->line,
                err->int2,
                err->code,
                err->message);
    }
    xmlFreeTextReader(reader);
    xmlCleanupParser();
    return buf;
}

int main()
{
    // Used for testing
    char *res;
    // Your args here
    // res = validateXml();
    if (res != NULL)
    {
        printf(stdout, "res != NULL");
    }
    return 0;
}