#!/bin/bash

set -euo pipefail

CONFIG_DIR="/openair-smf/etc"

# Default values
# (Default NWI Domain for all UPFs in OAI-Integration)
USE_NETWORK_INSTANCE=${USE_NETWORK_INSTANCE:-no}
DOMAIN_ACCESS=${DOMAIN_ACCESS:-access.oai.org}
DOMAIN_CORE=${DOMAIN_CORE:-core.oai.org}

if [[ ${USE_FQDN_DNS} == "yes" ]];then
    AMF_IPV4_ADDRESS=${AMF_IPV4_ADDRESS:-0.0.0.0}
    NRF_IPV4_ADDRESS=${NRF_IPV4_ADDRESS:-0.0.0.0}
    UPF_IPV4_ADDRESS=${UPF_IPV4_ADDRESS:-0.0.0.0}
    UDM_IPV4_ADDRESS=${UDM_IPV4_ADDRESS:-0.0.0.0}
fi
HTTP_VERSION=${HTTP_VERSION:-1}

for c in ${CONFIG_DIR}/*.conf; do
    # grep variable names (format: ${VAR}) from template to be rendered
    VARS=$(grep -oP '@[a-zA-Z0-9_]+@' ${c} | sort | uniq | xargs)
    echo "Now setting these variables '${VARS}'"

    # create sed expressions for substituting each occurrence of ${VAR}
    # with the value of the environment variable "VAR"
    EXPRESSIONS=""
    for v in ${VARS}; do
        NEW_VAR=`echo $v | sed -e "s#@##g"`
        if [[ -z ${!NEW_VAR+x} ]]; then
            echo "Error: Environment variable '${NEW_VAR}' is not set." \
                "Config file '$(basename $c)' requires all of $VARS."
            exit 1
        fi
        EXPRESSIONS="${EXPRESSIONS};s|${v}|${!NEW_VAR}|g"
    done
    EXPRESSIONS="${EXPRESSIONS#';'}"

    # render template and inline replace config file
    sed -i "${EXPRESSIONS}" ${c}
done
echo "Done setting the configuration"
exec "$@"
